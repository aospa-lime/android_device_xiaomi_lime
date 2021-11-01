/*
   Copyright (c) 2015, The Linux Foundation. All rights reserved.
   Copyright (C) 2016 The CyanogenMod Project.
   Copyright (C) 2019-2020 The LineageOS Project.
   Copyright (C) 2021 Paranoid Android.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.
   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <android-base/properties.h>
#include <fstream>
#include <unistd.h>
#include <vector>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include "property_service.h"
#include "vendor_init.h"

#include <sys/_system_properties.h>

using android::base::GetProperty;

std::vector<std::string> ro_props_default_source_order = {
    "",
    "product.",
    "system.",
    "vendor.",
};

void property_override(char const prop[], char const value[], bool add = true) {
    prop_info *pi;

    pi = (prop_info *)__system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void vendor_load_properties() {
    const auto set_ro_build_prop = [](const std::string &source, const std::string &prop, const std::string &value) {
        auto prop_name = "ro." + source + "build." + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    const auto set_ro_product_prop = [](const std::string &source, const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    std::string region = GetProperty("ro.boot.hwc", "");
    std::string hwname = GetProperty("ro.boot.product.hardware.sku", "");
    if (hwname == "lime") {
        if (region == "CN" || region == "Japan") {
            property_override("ro.product.brand", "Redmi");
            property_override("ro.product.model", "Redmi 9 Power");
            property_override("ro.product.device", "lime");
        }
        if (region == "India") {
            property_override("ro.product.brand", "Redmi");
            property_override("ro.product.model", "Redmi Note 9 4G");
            property_override("ro.product.device", "lime");
        }
        if (region == "Global") {
            property_override("ro.product.brand", "Redmi");
            property_override("ro.product.model", "Redmi 9T");
            property_override("ro.product.device", "lime");
        }
    } else if (hwname == "lemon") {
        property_override("ro.product.brand", "Redmi");
        property_override("ro.product.model", "Redmi 9T NFC");
        property_override("ro.product.device", "lemon");
    } else if (hwname == "citrus") {
        property_override("ro.product.brand", "POCO");
        property_override("ro.product.model", "POCO M3");
        property_override("ro.product.device", "citrus");
    } else if (hwname == "pomelo") {
        property_override("ro.product.brand", "Redmi");
        property_override("ro.product.model", "Redmi 9T");
        property_override("ro.product.device", "pomelo");
    }
}
