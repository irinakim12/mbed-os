/*
 * Copyright (c) 2019, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "greentea-client/test_env.h"
#include "mbed.h"
#include "TLSSocket.h"
#include "unity/unity.h"
#include "utest.h"
#include "tls_tests.h"

using namespace utest::v1;

#if defined(MBEDTLS_SSL_CLI_C)

void TLSSOCKET_OPEN_DESTRUCT()
{
#if MBED_CONF_NSAPI_SOCKET_STATS_ENABLE
    int count = fetch_stats();
    for (int j = 0; j < count; j++) {
        TEST_ASSERT_EQUAL(SOCK_CLOSED,  tls_stats[j].state);
    }
#endif

    for (int i = 0; i < 1000; i++) {
        TLSSocket *sock = new TLSSocket;
        if (!sock) {
            TEST_FAIL();
        }
        TEST_ASSERT_EQUAL(NSAPI_ERROR_OK, sock->open(NetworkInterface::get_default_instance()));
        delete sock;
    }
#if MBED_CONF_NSAPI_SOCKET_STATS_ENABLE
    count = fetch_stats();
    for (int j = 0; j < count; j++) {
        TEST_ASSERT_EQUAL(SOCK_CLOSED, tls_stats[j].state);
    }
#endif
}

#endif // defined(MBEDTLS_SSL_CLI_C)