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

#ifndef __KMS_SIP_SRTP_CONNECTION_H__
#define __KMS_SIP_SRTP_CONNECTION_H__

#include "kmsrtpbaseconnection.h"

G_BEGIN_DECLS

#define KMS_TYPE_SIP_SRTP_CONNECTION \
  (kms_sip_srtp_connection_get_type())
#define KMS_SIP_SRTP_CONNECTION(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj),KMS_TYPE_SIP_SRTP_CONNECTION,KmsSipSrtpConnection))
#define KMS_SRTP_CONNECTION_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass),KMS_TYPE_SIP_SRTP_CONNECTION,KmsSipSrtpConnectionClass))
#define KMS_IS_SIP_SRTP_CONNECTION(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj),KMS_TYPE_SIP_SRTP_CONNECTION))
#define KMS_IS_SIP_SRTP_CONNECTION_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass),KMS_TYPE_SIP_SRTP_CONNECTION))
#define KMS_SIP_SRTP_CONNECTION_CAST(obj) ((KmsSipSrtpConnection*)(obj))

typedef struct _KmsSipSrtpConnectionPrivate KmsSipSrtpConnectionPrivate;
typedef struct _KmsSipSrtpConnection KmsSipSrtpConnection;
typedef struct _KmsSipSrtpConnectionClass KmsSipSrtpConnectionClass;

struct _KmsSipSrtpConnection
{
  KmsRtpBaseConnection parent;

  KmsSipSrtpConnectionPrivate *priv;
};

struct _KmsSipSrtpConnectionClass
{
  KmsRtpBaseConnectionClass parent_class;

  /* signals */
  void (*key_soft_limit) (KmsSipSrtpConnection *conn);
};

GType kms_sip_srtp_connection_get_type (void);

KmsSipSrtpConnection *kms_sip_srtp_connection_new (guint16 min_port, guint16 max_port, gboolean use_ipv6);
void kms_sip_srtp_connection_set_key (KmsSipSrtpConnection *conn, const gchar *key, guint auth, guint cipher, gboolean local);

G_END_DECLS
#endif /* __KMS_SIP_RTP_CONNECTION_H__ */
