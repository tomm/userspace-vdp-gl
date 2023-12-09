#include "fake_fabgl.h"
#include <unordered_map>
#include <mutex>

//#define LIMIT_ESP32_RAM

// How much memory is already used by static data on VDP startup.
// Values arrived at by examining free heap ram on a real Agon,
// and subtracting what is dynamically allocated on an emulator startup.
// XXX highly fishy values. need to be updated with VDP version changes
#define IRAM_OVERHEAD 163712
#define DRAM_OVERHEAD 110920 // considering esp_get_free_internal_heap_size()
#define PSRAM_OVERHEAD 12397

enum Esp32MemType {
	IRam,
	DRam,
	PSRam,
	Max
};

static Esp32MemType esp32MemTypeFromCaps(int caps)
{
	if (caps & MALLOC_CAP_DMA) {
		return Esp32MemType::DRam;
	} else if (caps & MALLOC_CAP_SPIRAM || !(caps & MALLOC_CAP_INTERNAL)) {
		return Esp32MemType::PSRam;
	} else if (caps & MALLOC_CAP_32BIT) {
		return Esp32MemType::IRam;
	} else {
		return Esp32MemType::DRam;
	}
}

struct Esp32Alloc {
	Esp32MemType type;
	size_t size;
	Esp32Alloc(Esp32MemType _type, size_t _size): type(_type), size(_size) {}
};

class EspRam {
private:
	std::mutex _lock;
	size_t esp_ram_free[(size_t)Esp32MemType::Max];
	std::unordered_map<void *, Esp32Alloc> allocs;
public:
	EspRam() {
		esp_ram_free[IRam] = 200*1024 - IRAM_OVERHEAD;
		esp_ram_free[DRam] = 320*1024 - DRAM_OVERHEAD;
		esp_ram_free[PSRam] = 4*1024*1024 - PSRAM_OVERHEAD;
	}

	std::unique_lock<std::mutex> acquireLock() {
		return std::unique_lock<std::mutex>(_lock);
	}

	void dump_mem_stats()
	{
		printf("ESP32 free RAM: IRAM %ld bytes, DRAM %ld bytes, PSRAM %ld bytes\n", 
				esp_ram_free[Esp32MemType::IRam],
				esp_ram_free[Esp32MemType::DRam],
				esp_ram_free[Esp32MemType::PSRam]);
	}

	void *alloc(size_t sz, int caps)
	{
		auto lock = acquireLock();
		const Esp32MemType type = esp32MemTypeFromCaps(caps);
#ifdef LIMIT_ESP32_RAM
		if (esp_ram_free[type] < sz) {
			printf("ESP32 out of ram (caps 0x%x)!\n", caps);
			return nullptr;
		}
#endif /* LIMIT_ESP32_RAM */
		void *p = ::malloc(sz);
		esp_ram_free[type] -= sz;
		allocs.emplace(std::make_pair(p, Esp32Alloc(type, sz)));
		return p;
	}

	void *dealloc(void *p)
	{
		::free(p);
		auto lock = acquireLock();
		auto iter = allocs.find(p);
		if (iter != allocs.end()) {
			esp_ram_free[iter->second.type] += iter->second.size;
			allocs.erase(iter);
		}
		return p;
	}

	size_t get_free_size(int caps) {
#ifdef LIMIT_ESP32_RAM
		auto lock = acquireLock();
		const Esp32MemType type = esp32MemTypeFromCaps(caps);
		return esp_ram_free[type];
#else
		return 1024*1024*4;
#endif /* LIMIT_ESP32_RAM */
	}
};

static EspRam *_ram = nullptr;

static inline EspRam *ram() {
	if (_ram == nullptr) _ram = new EspRam();
	return _ram;
}

void init_esp_ram()
{
	//ram = new EspRam();
}

void *heap_caps_malloc(size_t sz, int caps) {
	return ram()->alloc(sz, caps);
}

/*
void *heap_caps_realloc(void *ptr, size_t sz, int) {
	return realloc(ptr, sz);
}
*/

void *heap_caps_free(void *ptr) {
	return ram()->dealloc(ptr);
}

size_t heap_caps_get_largest_free_block(int caps) {
	// XXX no heap fragmentation emulated, so largest free block is total free
	return ram()->get_free_size(caps);
}

int heap_caps_get_free_size(int caps) {
	return ram()->get_free_size(caps);
}

void malloc_wrapper_dump_stats() {
	ram()->dump_mem_stats();
}
