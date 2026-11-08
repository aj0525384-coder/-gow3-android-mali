
package com.example.gpuinfo

import android.app.Activity
import android.os.Bundle
import android.widget.TextView
import android.widget.ScrollView
import android.view.Gravity

class MainActivity : Activity() {

    companion object {
        init {
            System.loadLibrary("gow3_gpu")
        }
    }

    external fun getVulkanInfo(): String

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        val output = TextView(this).apply {
            textSize = 17f
            setPadding(32, 40, 32, 40)
            gravity = Gravity.START
            text = "GO W3 ANDROID - MALI EDITION\n\n" +
                    getVulkanInfo()
        }

        val scroll = ScrollView(this)
        scroll.addView(output)
        setContentView(scroll)
    }
}
