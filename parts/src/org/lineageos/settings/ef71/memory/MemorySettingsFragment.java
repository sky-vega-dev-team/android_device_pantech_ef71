/*
 * Copyright (C) 2026 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

package org.lineageos.settings.ef71.memory;

import android.os.Bundle;
import android.os.SystemProperties;
import android.widget.Switch;

import androidx.preference.PreferenceFragment;

import com.android.settingslib.widget.MainSwitchPreference;
import com.android.settingslib.widget.OnMainSwitchChangeListener;

import org.lineageos.settings.ef71.R;

import java.io.File;

public class MemorySettingsFragment extends PreferenceFragment
        implements OnMainSwitchChangeListener {

    private static final String PREF_ENABLE = "mglru_enable";

    /* init.ef71.parts.rc writes this to /sys/kernel/mm/lru_gen/enabled */
    private static final String PROP_MGLRU = "persist.sys.ef71.mglru";
    private static final File LRU_GEN_ENABLED = new File("/sys/kernel/mm/lru_gen/enabled");

    @Override
    public void onCreatePreferences(Bundle savedInstanceState, String rootKey) {
        addPreferencesFromResource(R.xml.memory_settings);

        MainSwitchPreference switchBar = findPreference(PREF_ENABLE);
        switchBar.setChecked(SystemProperties.getBoolean(PROP_MGLRU, false));
        switchBar.addOnSwitchChangeListener(this);

        if (!LRU_GEN_ENABLED.exists()) {
            switchBar.setEnabled(false);
            switchBar.setTitle(R.string.mglru_unsupported);
        }
    }

    @Override
    public void onSwitchChanged(Switch switchView, boolean isChecked) {
        SystemProperties.set(PROP_MGLRU, isChecked ? "1" : "0");
    }
}
