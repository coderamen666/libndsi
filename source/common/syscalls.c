#include <ndsi/ndstypes.h>
#include <ndsi/system.h>
#include <ndsi/bios.h>

int swiDecompressLZSSVram(void * source, void * destination, uint32 toGetSize, TDecompressionStream * stream) {

	if (isDSiMode()) {
		return swiDecompressLZSSVramTWL(source,destination,toGetSize,stream);
	} else {
		return swiDecompressLZSSVramNTR(source,destination,toGetSize,stream);
	}
	
}
