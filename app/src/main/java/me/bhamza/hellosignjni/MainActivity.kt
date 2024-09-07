package me.bhamza.hellosignjni

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import me.bhamza.hellosignjni.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.signBtn.setOnClickListener {
             val signature = sign(binding.inputMessage.text.toString())
            binding.signResult.text = signature
            // binding.signResult.text = stringFromJNI()
        }
    }

    /**
     * A native method that is implemented by the 'HelloSignJNI' native library,
     */
    external fun sign(input_str : String): String

    companion object {
        // Used to load the 'HelloSignJNI' library on application startup.
        init {
            System.loadLibrary("hellosignjni")
        }
    }
}
