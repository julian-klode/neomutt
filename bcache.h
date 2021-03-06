/**
 * Copyright (C) 2006-2007 Brendan Cully <brendan@kublai.com>
 * Copyright (C) 2006 Rocco Rutte <pdmef@gmx.net>
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

#ifndef _MUTT_BCACHE_H
#define _MUTT_BCACHE_H 1

#include <stdio.h>

struct Account;
struct BodyCache;

/*
 * Parameters:
 *   - 'account' is the current mailbox' account (required)
 *   - 'mailbox' is the path to the mailbox of the account (optional):
 *     the driver using it is responsible for ensuring that hierarchies
 *     are separated by '/' (if it knows of such a concepts like
 *     mailboxes or hierarchies)
 * Returns NULL on failure.
 */
struct BodyCache *mutt_bcache_open(struct Account *account, const char *mailbox);

/* free all memory of bcache and finally FREE() it, too */
void mutt_bcache_close(struct BodyCache **bcache);

/*
 * Parameters:
 *   - 'bcache' is the pointer returned by mutt_bcache_open() (required)
 *   - 'id' is a per-mailbox unique identifier for the message (required)
 * These return NULL/-1 on failure and FILE pointer/0 on success.
 */

FILE *mutt_bcache_get(struct BodyCache *bcache, const char *id);
/* tmp: the returned FILE* is in a temporary location.
 *      if set, use mutt_bcache_commit to put it into place */
FILE *mutt_bcache_put(struct BodyCache *bcache, const char *id, int tmp);
int mutt_bcache_commit(struct BodyCache *bcache, const char *id);
int mutt_bcache_del(struct BodyCache *bcache, const char *id);
int mutt_bcache_exists(struct BodyCache *bcache, const char *id);

/*
 * This more or less "examines" the cache and calls a function with
 * each id it finds if given.
 *
 * The optional callback function gets the id of a message, the very same
 * body cache handle mutt_bcache_list() is called with (to, perhaps,
 * perform further operations on the bcache), and a data cookie which is
 * just passed as-is. If the return value of the callback is non-zero, the
 * listing is aborted and continued otherwise. The callback is optional
 * so that this function can be used to count the items in the cache
 * (see below for return value).
 *
 * This returns -1 on failure and the count (>=0) of items processed
 * otherwise.
 */
int mutt_bcache_list(struct BodyCache *bcache,
                     int (*want_id)(const char *id, struct BodyCache *bcache, void *data),
                     void *data);

#endif /* _MUTT_BCACHE_H */
