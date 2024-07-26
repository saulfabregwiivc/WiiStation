/* SPDX-License-Identifier: LGPL-2.1-or-later */
/*
 * Copyright (C) 2019-2021 Paul Cercueil <paul@crapouillou.net>
 */

#ifndef __LIGHTREC_CONFIG_H__
#define __LIGHTREC_CONFIG_H__

#define ENABLE_THREADED_COMPILER 0
#define ENABLE_FIRST_PASS 1
#define ENABLE_DISASSEMBLER 0
#define ENABLE_CODE_BUFFER 1

#define HAS_DEFAULT_ELM 1

#define OPT_REMOVE_DIV_BY_ZERO_SEQ 1
#define OPT_REPLACE_MEMSET 1
#define OPT_DETECT_IMPOSSIBLE_BRANCHES 1
#define OPT_HANDLE_LOAD_DELAYS 1
#define OPT_TRANSFORM_OPS 1
#define OPT_LOCAL_BRANCHES 1
#define OPT_SWITCH_DELAY_SLOTS 1
#define OPT_FLAG_IO 1
#define OPT_FLAG_MULT_DIV 1
#define OPT_EARLY_UNLOAD 1
#define OPT_PRELOAD_PC 1

#define OPT_SH4_USE_GBR 0

#endif /* __LIGHTREC_CONFIG_H__ */

