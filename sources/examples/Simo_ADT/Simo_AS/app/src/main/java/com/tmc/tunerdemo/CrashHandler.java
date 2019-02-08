package com.tmc.tunerdemo; 


import android.app.Activity; 
import android.app.AlertDialog; 
import android.app.ProgressDialog; 
import android.content.Intent; 
import android.content.SharedPreferences; 
import android.net.MailTo; 
import android.os.AsyncTask; 
 import android.os.Build; 
 import android.os.Bundle; 
 import android.util.Log; 
 import android.view.View; 
 import android.widget.Button; 
 import android.widget.CheckBox; 
 import android.widget.Toast; 
 import java.io.IOException; 
 import java.text.MessageFormat; 
 import java.util.ArrayList; 
 import java.util.concurrent.TimeUnit; 
 import java.util.concurrent.TimeoutException; 
 

 public class CrashHandler extends Activity 
 { 
 	public static final String TAG = "CrashHandler"; 
 	protected void onCreate(Bundle state) 
 	{ 
 		super.onCreate(state); 
 		setTitle("Exception in TMC application"); 

		final Button  button = new Button(this);
		button.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				button.setText( "Done");
				finish();
			}
		});
		button.setText( "Sorry, Exception in TMC application\n Check ServoToolErr.txt file\n Press to Close");
	    setContentView(button);

  	} 

 } 

 








  





