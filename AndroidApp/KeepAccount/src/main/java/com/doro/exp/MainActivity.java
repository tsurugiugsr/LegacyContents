package com.doro.exp;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;
import android.widget.TextView;

import androidx.annotation.Nullable;

import com.doro.exp.dao.RecordDAO;

import java.math.BigDecimal;
import java.math.RoundingMode;

public class MainActivity extends Activity {
    private TextView todayIncomeTV;
    private TextView todayOutcomeTV;
    private TextView todayRemainTV;
    private TextView monthIncomeTV;
    private TextView monthOutcomeTV;
    private TextView monthRemainTV;
    private RecordDAO recordDAO;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        recordDAO = new RecordDAO(MainActivity.this);
        ImageButton addRecordButton = (ImageButton) findViewById(R.id.activityMain_addRecord);
        ImageButton listRecordButton = (ImageButton) findViewById(R.id.activityMain_listRecords);
        todayIncomeTV = (TextView) findViewById(R.id.activityMain_tagTodayTotalIncome);
        todayOutcomeTV = (TextView) findViewById(R.id.activityMain_tagTodayTotalOutcome);
        todayRemainTV = (TextView) findViewById(R.id.activityMain_tagTodayTotalRemain);
        monthIncomeTV = (TextView) findViewById(R.id.activityMain_tagMonthTotalIncome);
        monthOutcomeTV = (TextView) findViewById(R.id.activityMain_tagMonthTotalOutcome);
        monthRemainTV = (TextView) findViewById(R.id.activityMain_tagMonthTotalRemain);

        addRecordButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, AddAccountActivity.class);
                startActivityForResult(intent, 0x715);
            }
        });

        listRecordButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(MainActivity.this, ListRecordSelectActivity.class);
                startActivityForResult(intent, 0x715);
            }
        });

        setTextView();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if(requestCode == 0x715 && resultCode == 0x715) {
            setTextView();
        }
    }

    public void setTextView() {
        long currentTime = System.currentTimeMillis();
        java.util.Calendar calendar = java.util.Calendar.getInstance();
        // 月末时间
        calendar.setTimeInMillis(currentTime);
        calendar.add(java.util.Calendar.YEAR, 0);
        calendar.add(java.util.Calendar.MONTH, 0);
        calendar.set(java.util.Calendar.DAY_OF_MONTH, 0);
        calendar.set(java.util.Calendar.HOUR_OF_DAY, 0);
        calendar.set(java.util.Calendar.MINUTE, 0);
        calendar.set(java.util.Calendar.SECOND, 0);
        calendar.set(java.util.Calendar.MILLISECOND, 0);
        long dayStartTime = calendar.getTimeInMillis();
        // 月初时间
        calendar.setTimeInMillis(currentTime);
        calendar.add(java.util.Calendar.YEAR, 0);
        calendar.add(java.util.Calendar.MONTH, 0);
        calendar.set(java.util.Calendar.DAY_OF_MONTH, 1);
        calendar.set(java.util.Calendar.HOUR_OF_DAY, 0);
        calendar.set(java.util.Calendar.MINUTE, 0);
        calendar.set(java.util.Calendar.SECOND, 0);
        calendar.set(java.util.Calendar.MILLISECOND, 0);
        long monthStartTime = calendar.getTimeInMillis();
        double dayIncome = recordDAO.getIncomeByStartTimeAndEndTime(dayStartTime, currentTime);
        double dayOutcome = recordDAO.getOutcomeByStartTimeAndEndTime(dayStartTime, currentTime);
        double dayRemain = dayIncome - dayOutcome;
        double monthIncome = recordDAO.getIncomeByStartTimeAndEndTime(monthStartTime, currentTime);
        double monthOutcome = recordDAO.getOutcomeByStartTimeAndEndTime(monthStartTime, currentTime);
        double monthRemain = monthIncome - monthOutcome;
        todayIncomeTV.setText(String.valueOf(new BigDecimal(dayIncome).setScale(2, RoundingMode.HALF_UP)));
        todayOutcomeTV.setText(String.valueOf(new BigDecimal(dayOutcome).setScale(2, RoundingMode.HALF_UP)));
        todayRemainTV.setText(String.valueOf(new BigDecimal(dayRemain).setScale(2, RoundingMode.HALF_UP)));
        monthIncomeTV.setText(String.valueOf(new BigDecimal(monthIncome).setScale(2, RoundingMode.HALF_UP)));
        monthOutcomeTV.setText(String.valueOf(new BigDecimal(monthOutcome).setScale(2, RoundingMode.HALF_UP)));
        monthRemainTV.setText(String.valueOf(new BigDecimal(monthRemain).setScale(2, RoundingMode.HALF_UP)));
    }
}
