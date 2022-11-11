package com.example.zhang.keepaccount;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import androidx.annotation.Nullable;

import com.example.zhang.keepaccount.dao.RecordDAO;
import com.example.zhang.keepaccount.dao.TagDAO;
import com.example.zhang.keepaccount.entity.Record;
import com.example.zhang.keepaccount.entity.Tag;

import java.util.List;
import java.util.Random;

/**
 * Created by zhang on 2022/4/17.
 */

public class MainActivity extends Activity{
    private RecordDAO recordDAO;
    private TagDAO tagDAO;
    private TextView textView;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_test);
        recordDAO = new RecordDAO(MainActivity.this);
        tagDAO = new TagDAO(MainActivity.this);
        textView = findViewById(R.id.tv);
    }


    /* record 测试相关接口*/
    public void save(View view) {
        Random random = new Random();
        Record record = new Record(System.currentTimeMillis(), random.nextDouble(), random.nextInt(2), random.nextInt(2), "comment" + random.nextInt(50));
        Uri newUri = recordDAO.saveRecord(record);
        textView.setText("");
        textView.setText(newUri.toString());
    }

    public void update(View view) {
        Random random = new Random();
        Record record = new Record(1, System.currentTimeMillis(), random.nextDouble(), random.nextInt(2), random.nextInt(2), "comment" + random.nextInt(50));
        int count = recordDAO.updateRecord(record);
        textView.setText("");
        textView.setText(String.valueOf(count));
    }

    public void getIncome(View view) {
        long currentTime = System.currentTimeMillis();
        java.util.Calendar calendar = java.util.Calendar.getInstance();
        // 月初时间
        calendar.setTimeInMillis(currentTime);
        calendar.add(java.util.Calendar.YEAR, 0);
        calendar.add(java.util.Calendar.MONTH, 0);
        calendar.set(java.util.Calendar.DAY_OF_MONTH, 1);
        calendar.set(java.util.Calendar.HOUR_OF_DAY, 0);
        calendar.set(java.util.Calendar.MINUTE, 0);
        calendar.set(java.util.Calendar.SECOND, 0);
        calendar.set(java.util.Calendar.MILLISECOND, 0);
        long startTime = calendar.getTimeInMillis();
        // 月末时间
        calendar.setTimeInMillis(currentTime);
        calendar.add(java.util.Calendar.YEAR, 0);
        calendar.add(java.util.Calendar.MONTH, 0);
        calendar.set(java.util.Calendar.DAY_OF_MONTH, calendar.getActualMaximum(java.util.Calendar.DAY_OF_MONTH));
        calendar.set(java.util.Calendar.HOUR_OF_DAY, 23);
        calendar.set(java.util.Calendar.MINUTE, 59);
        calendar.set(java.util.Calendar.SECOND, 59);
        calendar.set(java.util.Calendar.MILLISECOND, 999);
        long endTime = calendar.getTimeInMillis();
        double ans = recordDAO.getIncomeByStartTimeAndEndTime(startTime, endTime);
        textView.setText("");
        textView.setText(String.valueOf(ans));
    }

    public void getOutcome(View view) {
        long currentTime = System.currentTimeMillis();
        java.util.Calendar calendar = java.util.Calendar.getInstance();
        // 月初时间
        calendar.setTimeInMillis(currentTime);
        calendar.add(java.util.Calendar.YEAR, 0);
        calendar.add(java.util.Calendar.MONTH, 0);
        calendar.set(java.util.Calendar.DAY_OF_MONTH, 1);
        calendar.set(java.util.Calendar.HOUR_OF_DAY, 0);
        calendar.set(java.util.Calendar.MINUTE, 0);
        calendar.set(java.util.Calendar.SECOND, 0);
        calendar.set(java.util.Calendar.MILLISECOND, 0);
        long startTime = calendar.getTimeInMillis();
        // 月末时间
        calendar.setTimeInMillis(currentTime);
        calendar.add(java.util.Calendar.YEAR, 0);
        calendar.add(java.util.Calendar.MONTH, 0);
        calendar.set(java.util.Calendar.DAY_OF_MONTH, calendar.getActualMaximum(java.util.Calendar.DAY_OF_MONTH));
        calendar.set(java.util.Calendar.HOUR_OF_DAY, 23);
        calendar.set(java.util.Calendar.MINUTE, 59);
        calendar.set(java.util.Calendar.SECOND, 59);
        calendar.set(java.util.Calendar.MILLISECOND, 999);
        long endTime = calendar.getTimeInMillis();
        double ans = recordDAO.getOutcomeByStartTimeAndEndTime(startTime, endTime);
        textView.setText("");
        textView.setText(String.valueOf(ans));
    }

    public void getListByTime(View view) {
        long currentTime = System.currentTimeMillis();
        java.util.Calendar calendar = java.util.Calendar.getInstance();
        // 月初时间
        calendar.setTimeInMillis(currentTime);
        calendar.add(java.util.Calendar.YEAR, 0);
        calendar.add(java.util.Calendar.MONTH, 0);
        calendar.set(java.util.Calendar.DAY_OF_MONTH, 1);
        calendar.set(java.util.Calendar.HOUR_OF_DAY, 0);
        calendar.set(java.util.Calendar.MINUTE, 0);
        calendar.set(java.util.Calendar.SECOND, 0);
        calendar.set(java.util.Calendar.MILLISECOND, 0);
        long startTime = calendar.getTimeInMillis();
        // 月末时间
        calendar.setTimeInMillis(currentTime);
        calendar.add(java.util.Calendar.YEAR, 0);
        calendar.add(java.util.Calendar.MONTH, 0);
        calendar.set(java.util.Calendar.DAY_OF_MONTH, calendar.getActualMaximum(java.util.Calendar.DAY_OF_MONTH));
        calendar.set(java.util.Calendar.HOUR_OF_DAY, 23);
        calendar.set(java.util.Calendar.MINUTE, 59);
        calendar.set(java.util.Calendar.SECOND, 59);
        calendar.set(java.util.Calendar.MILLISECOND, 999);
        long endTime = calendar.getTimeInMillis();
        List<Record> records = recordDAO.getRecordListByStartTimeAndEndTime(startTime, endTime);
        textView.setText("");
        textView.setText(records.toString());
    }

    public void getListByTag(View view) {
        List<Record> records = recordDAO.getRecordListByTagId(0);
        textView.setText("");
        textView.setText(records.toString());
    }

    public void delete(View view) {
        int delete = recordDAO.deleteRecordById(8);
        textView.setText("");
        textView.setText(String.valueOf(delete));
    }

    /* tag 测试相关接口 */
    public void saveTag(View view) {
        Random random = new Random();
        Tag tag = new Tag("name" + random.nextInt(50), random.nextInt(2));
        Uri newUri = tagDAO.saveTag(tag);
        textView.setText("");
        textView.setText(newUri.toString());
    }

    public void getTagList(View view) {
        List<Tag> tags = tagDAO.getTagList();
        textView.setText("");
        textView.setText(tags.toString());
    }

    public void deleteTag(View view) {
        int delete = tagDAO.deleteRecordById(4);
        textView.setText("");
        textView.setText(String.valueOf(delete));
    }

    public void enterTagAct(View view) {
        Intent intent = new Intent(MainActivity.this,AddTagActivity.class);
        startActivity(intent);

    }

    public void enterListTag(View view) {
        Intent intent = new Intent(MainActivity.this,ListRecordByTagActivity.class);
        startActivity(intent);
    }

}
