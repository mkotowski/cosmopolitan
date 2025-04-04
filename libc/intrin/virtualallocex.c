/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│ vi: set et ft=c ts=2 sts=2 sw=2 fenc=utf-8                               :vi │
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2024 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/calls/syscall_support-nt.internal.h"
#include "libc/intrin/describeflags.h"
#include "libc/intrin/strace.h"
#include "libc/nt/memory.h"
#include "libc/nt/thunk/msabi.h"

__msabi extern typeof(VirtualAllocEx) *const __imp_VirtualAllocEx;

/**
 * Allocates memory on The New Technology.
 */
textwindows void *VirtualAllocEx(int64_t hProcess, void *lpAddress,
                                 uint64_t dwSize, uint32_t flAllocationType,
                                 uint32_t flProtect) {
  void *res = __imp_VirtualAllocEx(hProcess, lpAddress, dwSize,
                                   flAllocationType, flProtect);
  if (!res)
    __winerr();
  NTTRACE("VirtualAllocEx(%ld, %p, %'lu, %s, %s) → %p% m", hProcess, lpAddress,
          dwSize, DescribeNtAllocationType(flAllocationType),
          DescribeNtPageFlags(flProtect), res);
  return res;
}
