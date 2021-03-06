/*
 *  Copyright (C) 2011 John Törnblom
 *
 * This file is part of TVHGuide.
 *
 * TVHGuide is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TVHGuide is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with TVHGuide.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __TVHPLAYER_H__
#define __TVHPLAYER_H__

#include <android/log.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <pthread.h>

#include "opensles.h"
#include "surface.h"

#define TAG "TVHPlayer"

#define DEBUG(fmt, args...)			\
  __android_log_print(ANDROID_LOG_DEBUG, TAG, "%s:%d: " fmt, __FUNCTION__, __LINE__, ##args);
#define INFO(args...)					\
  __android_log_print(ANDROID_LOG_INFO, TAG, args)
#define ERROR(args...)					\
  __android_log_print(ANDROID_LOG_ERROR, TAG, args)

typedef struct acodec_sys {
  AVCodecContext * ctx;
  AVCodec        * codec;
  unsigned short * buf;
  size_t           len;
} acodec_sys_t;

typedef struct vcodec_sys {
  AVCodecContext    * ctx;
  AVCodec           * codec;
  AVFrame           * frame;
  struct SwsContext * conv;
} vcodec_sys_t;

typedef struct tvh_object {
  aout_sys_t     * ao;
  vout_sys_t     * vo;
  acodec_sys_t   * acs;
  vcodec_sys_t   * vcs;
  int              running;
  int64_t          cur_pts;
  pthread_t        thread;
  pthread_mutex_t  mutex;
} tvh_object_t;


int tvh_init(tvh_object_t *tvh);
void tvh_start(tvh_object_t *tvh);
void tvh_stop(tvh_object_t *tvh);
void tvh_destroy(tvh_object_t *tvh);

int tvh_video_init(tvh_object_t *tvh, const char *codec);
void tvh_video_enqueue(tvh_object_t *tvh, uint8_t *buf, size_t len, int64_t pts, int64_t dts, int64_t dur);

int tvh_audio_init(tvh_object_t *tvh, const char *codec);
int tvh_audio_enqueue(tvh_object_t *tvh, uint8_t *buf, size_t len, int64_t pts, int64_t dts, int64_t dur);

#endif
