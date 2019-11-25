/*
 * (C) Copyright 2015 Kurento (http://kurento.org/)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "kmssipsrtpsession.h"

#define GST_DEFAULT_NAME "kmssipsrtpsession"
#define GST_CAT_DEFAULT kms_sip_srtp_session_debug
GST_DEBUG_CATEGORY_STATIC (GST_CAT_DEFAULT);

#define kms_sip_srtp_session_parent_class parent_class

G_DEFINE_TYPE (KmsSipSrtpSession, kms_sip_srtp_session, KMS_TYPE_SRTP_SESSION);

KmsSipSrtpSession *
kms_sip_srtp_session_new (KmsBaseSdpEndpoint * ep, guint id,
    KmsIRtpSessionManager * manager, gboolean use_ipv6)
{
  GObject *obj;
  KmsSipSrtpSession *self;

  obj = g_object_new (KMS_TYPE_SIP_SRTP_SESSION, NULL);
  self = KMS_SIP_SRTP_SESSION (obj);
  KMS_SRTP_SESSION_CLASS (G_OBJECT_GET_CLASS (self))->post_constructor
      (KMS_SRTP_SESSION(self), ep, id, manager, use_ipv6);

  return self;
}

/* Connection management begin */

//KmsRtpBaseConnection *
//kms_sip_srtp_session_get_connection (KmsSipSrtpSession * self,
//    KmsSdpMediaHandler * handler)
//{
//  KmsBaseRtpSession *base_rtp_sess = KMS_BASE_RTP_SESSION (self);
//  KmsIRtpConnection *conn;
//
//  conn = kms_base_rtp_session_get_connection (base_rtp_sess, handler);
//  if (conn == NULL) {
//    return NULL;
//  }
//
//  return KMS_RTP_BASE_CONNECTION (conn);
//}

static KmsIRtpConnection *
kms_sip_srtp_session_create_connection (KmsBaseRtpSession * base_rtp_sess,
    const GstSDPMedia * media, const gchar * name, guint16 min_port,
    guint16 max_port)
{
  KmsSrtpConnection *conn = kms_srtp_connection_new (min_port, max_port,
      KMS_SRTP_SESSION (base_rtp_sess)->use_ipv6);

  return KMS_I_RTP_CONNECTION (conn);
}

/* Connection management end */

static void
kms_sip_srtp_session_post_constructor (KmsSrtpSession * self,
    KmsBaseSdpEndpoint * ep, guint id, KmsIRtpSessionManager * manager,
    gboolean use_ipv6)
{
  KmsBaseRtpSession *base_rtp_session = KMS_BASE_RTP_SESSION (self);

  self->use_ipv6 = use_ipv6;
  KMS_BASE_RTP_SESSION_CLASS (parent_class)->post_constructor (base_rtp_session,
      ep, id, manager);
}

static void
kms_sip_srtp_session_init (KmsSipSrtpSession * self)
{
  /* nothing to do */
}

static void
kms_sip_srtp_session_class_init (KmsSipSrtpSessionClass * klass)
{
  GstElementClass *gstelement_class = GST_ELEMENT_CLASS (klass);
  KmsBaseRtpSessionClass *base_rtp_session_class;
  KmsSrtpSessionClass *srtp_session_class;

  GST_DEBUG_CATEGORY_INIT (GST_CAT_DEFAULT, GST_DEFAULT_NAME, 0,
      GST_DEFAULT_NAME);

  srtp_session_class = KMS_SRTP_SESSION_CLASS (klass);

  srtp_session_class->post_constructor = kms_sip_srtp_session_post_constructor;

  base_rtp_session_class = KMS_BASE_RTP_SESSION_CLASS (klass);
  /* Connection management */
  base_rtp_session_class->create_connection =
      kms_sip_srtp_session_create_connection;

  gst_element_class_set_details_simple (gstelement_class,
      "SipSrtpSession",
      "Generic",
      "Base bin to manage elements related with a SIP SRTP session.",
      "Saul Pablo Labajo Izquierdo <slabajo@naevatec.com>");
}
