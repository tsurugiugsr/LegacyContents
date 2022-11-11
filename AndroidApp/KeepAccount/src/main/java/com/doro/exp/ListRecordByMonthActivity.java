package com.doro.exp;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.Spinner;
import android.widget.TextView;


import androidx.annotation.Nullable;

import com.doro.exp.dao.RecordDAO;
import com.doro.exp.dao.TagDAO;
import com.doro.exp.entity.Record;
import com.doro.exp.entity.Tag;

import java.math.BigDecimal;
import java.math.RoundingMode;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by ASUS on 2022/4/23.
 */

public class ListRecordByMonthActivity  extends Activity {
    private ListView listView;
    private TextView incomeTV;
    private TextView outcomeTV;
    private TextView remainTV;
    private ImageButton leftBtn;
    private  ImageButton rightBtn;
    private TextView  month;
    private List<Tag> tags;
    private Map<Integer, Tag> tagMap;
    private List<Record> records;
    private List<Map<String, Object>> recordsMap;
    private long startTime;
    private long endTime;

    private TagDAO tagDAO;
    private RecordDAO recordDAO;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_account_list_by_month);
        listView =(ListView) findViewById(R.id.recordListByMonth);
        incomeTV = (TextView)findViewById(R.id.accountListByMonth_monthTotalIncome);
        outcomeTV = (TextView)findViewById(R.id.accountListByMonth_monthTotalOutcome);
        remainTV = (TextView)findViewById(R.id.accountListByMonth_monthTotalRemain);
        leftBtn =(ImageButton)findViewById(R.id.toLeft) ;
        rightBtn =(ImageButton)findViewById(R.id.toRight);
        //给月份设置一个初始值
        month =(TextView) findViewById(R.id.accountListByMonth);
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
        startTime = calendar.getTimeInMillis();
        // 月末时间
        calendar.setTimeInMillis(currentTime);
        calendar.add(java.util.Calendar.YEAR, 0);
        calendar.add(java.util.Calendar.MONTH, 0);
        calendar.set(java.util.Calendar.DAY_OF_MONTH, calendar.getActualMaximum(java.util.Calendar.DAY_OF_MONTH));
        calendar.set(java.util.Calendar.HOUR_OF_DAY, 23);
        calendar.set(java.util.Calendar.MINUTE, 59);
        calendar.set(java.util.Calendar.SECOND, 59);
        calendar.set(java.util.Calendar.MILLISECOND, 999);
        endTime = calendar.getTimeInMillis();

        tagDAO = new TagDAO(ListRecordByMonthActivity.this);
        recordDAO = new RecordDAO(ListRecordByMonthActivity.this);
        tags = tagDAO.getAllTagList();
        tagMap = new HashMap<>();
        for(Tag tag: tags) {
            tagMap.put(tag.getId(), tag);
        }
        //左右按键设置监听方法
       leftBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //月份减一
                endTime = startTime - 1;
                java.util.Calendar calendar = java.util.Calendar.getInstance();
                calendar.setTimeInMillis(endTime);
                calendar.add(java.util.Calendar.YEAR, 0);
                calendar.add(java.util.Calendar.MONTH, 0);
                calendar.set(java.util.Calendar.DAY_OF_MONTH, 1);
                calendar.set(java.util.Calendar.HOUR_OF_DAY, 0);
                calendar.set(java.util.Calendar.MINUTE, 0);
                calendar.set(java.util.Calendar.SECOND, 0);
                calendar.set(java.util.Calendar.MILLISECOND, 0);
                startTime = calendar.getTimeInMillis();
                getRecordListViewByMonth();
            }
        });
        rightBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //月份加一
                startTime = endTime + 1;
                java.util.Calendar calendar = java.util.Calendar.getInstance();
                calendar.setTimeInMillis(startTime);
                calendar.add(java.util.Calendar.YEAR, 0);
                calendar.add(java.util.Calendar.MONTH, 0);
                calendar.set(java.util.Calendar.DAY_OF_MONTH, calendar.getActualMaximum(java.util.Calendar.DAY_OF_MONTH));
                calendar.set(java.util.Calendar.HOUR_OF_DAY, 23);
                calendar.set(java.util.Calendar.MINUTE, 59);
                calendar.set(java.util.Calendar.SECOND, 59);
                calendar.set(java.util.Calendar.MILLISECOND, 999);
                endTime = calendar.getTimeInMillis();
                getRecordListViewByMonth();
            }
        });

        //删除记录
        listView.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> adapterView, View view, final int i, long l) {
                AlertDialog.Builder adBuilder = new AlertDialog.Builder(ListRecordByMonthActivity.this);
                adBuilder.setMessage("确认要删除记录吗？")
                        .setPositiveButton("确认", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                int recordId = records.get(i).getId();
                                recordDAO.deleteRecordById(recordId);
                                getRecordListViewByMonth();
                            }
                        }).setNegativeButton("取消", new DialogInterface.OnClickListener() {

                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                    }
                });
                AlertDialog alertDialog = adBuilder.create();
                alertDialog.show();
                return true;
            }
        });

        listView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                Record record = records.get(i);
                Intent intent = new Intent(ListRecordByMonthActivity.this, UpdateAccountActivity.class);
                Bundle bundle = new Bundle();
                bundle.putInt("id", record.getId());
                bundle.putLong("time", record.getTime());
                bundle.putDouble("count", record.getCount());
                bundle.putInt("type", record.getType());
                bundle.putInt("tagId", record.getTagId());
                bundle.putCharSequence("comment", record.getComment());
                intent.putExtras(bundle);
                startActivityForResult(intent, 0x717);
            }
        });
        getRecordListViewByMonth();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if(requestCode == 0x717 && resultCode == 0x717) {
            getRecordListViewByMonth();
        }
    }

    public void getRecordListViewByMonth() {
        records = recordDAO.getRecordListByStartTimeAndEndTime(startTime, endTime);
        BigDecimal income = new BigDecimal(0);
        BigDecimal outcome = new BigDecimal(0);
        // 日期格式
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy/MM/dd HH:mm");
        recordsMap = new ArrayList<>();
        for (Record record : records) {
            Map<String, Object> map = new HashMap<>();
            BigDecimal count = new BigDecimal(record.getCount()).setScale(2, RoundingMode.HALF_UP);
            if (record.getType() == 0) {
                income = income.add(new BigDecimal(record.getCount()));
            } else {
                outcome = outcome.add(new BigDecimal(record.getCount()));
                count = count.multiply(new BigDecimal(-1));
            }

            map.put("tagName", tagMap.get(record.getTagId()).getName());
            map.put("time", sdf.format(new Date(record.getTime())));
            map.put("id", record.getId());
            map.put("type", record.getType());
            map.put("count", String.valueOf(count));
            recordsMap.add(map);
        }
        income = income.setScale(2, RoundingMode.HALF_UP);
        outcome = outcome.setScale(2, RoundingMode.HALF_UP);
        BigDecimal remain = income.subtract(outcome).setScale(2, RoundingMode.HALF_UP);
        incomeTV.setText(String.valueOf(income));
        outcomeTV.setText(String.valueOf(outcome));
        remainTV.setText(String.valueOf(remain));

        SimpleDateFormat monthSDF = new SimpleDateFormat("yyyy年MM月");
        month.setText(monthSDF.format(new Date(startTime)));

        String[] from = {"tagName", "time", "id", "type", "count"};
        int[] to = {R.id.recordItem_tagName, R.id.recordItem_createTime, R.id.recordItem_recordId, R.id.recordItem_type, R.id.recordItem_recordCount};
        SimpleAdapter simpleAdapter = new SimpleAdapter(this, recordsMap, R.layout.record_item, from, to);
        listView.setAdapter(simpleAdapter);
    }
}
