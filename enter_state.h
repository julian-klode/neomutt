/**
 * Copyright (C) 2017 Richard Russon <rich@flatcap.org>
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MUTT_ENTER_STATE_H
#define _MUTT_ENTER_STATE_H 1

#include <stddef.h>
#include "lib.h"

struct EnterState
{
  wchar_t *wbuf;
  size_t wbuflen;
  size_t lastchar;
  size_t curpos;
  size_t begin;
  int tabs;
};

static inline struct EnterState *mutt_new_enter_state(void)
{
  return safe_calloc(1, sizeof(struct EnterState));
}

#endif /* _MUTT_ENTER_STATE_H */
