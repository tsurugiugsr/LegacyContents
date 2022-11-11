package com.doro.exp;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;

import androidx.annotation.Nullable;

public class ListRecordSelectActivity extends Activity {

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_account_list_select);

        Button monthButton = (Button) findViewById(R.id.listSelect_byMonth);
        Button tagButton = (Button) findViewById(R.id.listSelect_byTag);

        monthButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(ListRecordSelectActivity.this, ListRecordByMonthActivity.class);
                startActivity(intent);
            }
        });

        tagButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(ListRecordSelectActivity.this, ListRecordByTagActivity.class);
                startActivity(intent);
            }
        });
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if(keyCode == KeyEvent.KEYCODE_BACK){
            Intent intent = getIntent();
            setResult(0x715, intent);
            finish();
        }
        return super.onKeyDown(keyCode, event);
    }
}
