# Copyright (C) 2021 Paranoid Android
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# APEX
$(call inherit-product, $(SRC_TARGET_DIR)/product/updatable_apex.mk)

# GSI
$(call inherit-product, $(SRC_TARGET_DIR)/product/developer_gsi_keys.mk)

# Namespaces
PRODUCT_SOONG_NAMESPACES += \
    device/xiaomi/lime

# Shipping API
PRODUCT_SHIPPING_API_LEVEL := 29

# Copy fstab to ramdisk
PRODUCT_COPY_FILES += $(LOCAL_PATH)/init/default/fstab.default:$(TARGET_COPY_OUT_RAMDISK)/fstab.default

PRODUCT_USE_DYNAMIC_PARTITIONS := true
PRODUCT_PACKAGES += fastbootd

# Add default implementation of fastboot HAL.
PRODUCT_PACKAGES += android.hardware.fastboot@1.0-impl-mock

# Default kernel revision
TARGET_KERNEL_VERSION := 4.19
