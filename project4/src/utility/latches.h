#pragma once
#include "types.h"

#ifndef LATCHES_H
#define LATCHES_H

void bufferClear(){
	latch_fetch_decode latch_fetch_decode_old = { -1 };
	latch_fetch_decode latch_fetch_decode_new = { -1 };
	latch_decode_execute latch_decode_execute_old = { -1, -1, -1, -1, -1, -1, -1, -1 };
	latch_decode_execute latch_decode_execute_new = { -1, -1, -1, -1, -1, -1, -1, -1 };
	latch_execute_memory latch_execute_memory_old = { -1, -1, -1, -1 };
	latch_execute_memory latch_execute_memory_new = { -1, -1, -1, -1 };
	latch_memory_writeback latch_memory_writeback_old = { -1, -1, -1, -1, -1 };
	latch_memory_writeback latch_memory_writeback_new = { -1, -1, -1, -1, -1 };
}

latch_fetch_decode latch_fetch_decode_old = { -1 };
latch_fetch_decode latch_fetch_decode_new = { -1 };
latch_decode_execute latch_decode_execute_old = { -1, -1, -1, -1, -1, -1, -1, -1 };
latch_decode_execute latch_decode_execute_new = { -1, -1, -1, -1, -1, -1, -1, -1 };
latch_execute_memory latch_execute_memory_old = { -1, -1, -1, -1 };
latch_execute_memory latch_execute_memory_new = { -1, -1, -1, -1 };
latch_memory_writeback latch_memory_writeback_old = { -1, -1, -1, -1, -1 };
latch_memory_writeback latch_memory_writeback_new = { -1, -1, -1, -1, -1 };

#endif