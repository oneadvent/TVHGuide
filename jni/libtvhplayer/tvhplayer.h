#ifndef __TVHPLAYER_H__
#define __TVHPLAYER_H__

#include <android/log.h>  
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>

#include "opensles.h"
#include "surface.h"

#define TAG "TVHPlayer"

#define DEBUG(args...)					\
  __android_log_print(ANDROID_LOG_DEBUG, TAG, args)
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
  aout_sys_t    *ao;
  vout_sys_t    *vo;
  acodec_sys_t  *acs;
  vcodec_sys_t  *vcs;
  int            running;
} tvh_object_t;


int tvh_init(tvh_object_t *tvh);
void tvh_destroy(tvh_object_t *tvh);

int tvh_video_init(tvh_object_t *tvh, const char *codec);
void tvh_video_enqueue(tvh_object_t *tvh, uint8_t *buf, size_t len, uint64_t pts, uint64_t dts, uint64_t dur);
void tvh_video_close(tvh_object_t *tvh);

int tvh_audio_init(tvh_object_t *tvh, const char *codec);
void tvh_audio_enqueue(tvh_object_t *tvh, uint8_t *buf, size_t len);
int tvh_audio_close(tvh_object_t *tvh);

#endif