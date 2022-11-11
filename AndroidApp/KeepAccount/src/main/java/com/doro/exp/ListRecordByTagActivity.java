package com.doro.exp;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.SimpleCursorAdapter;
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
 * Created by zhang on 2022/4/22.
 */

public class ListRecordByTagActivity extends Activity{
    private ListView listView;
    private Spinner spinner;
    private TextView incomeTV;
    private TextView outcomeTV;
    private TextView remainTV;
    private Button button;

    private List<Tag> tags;
    private List<Record> records;
    private List<Map<String, Object>> recordsMap;

    private TagDAO tagDAO;
    private RecordDAO recordDAO;


    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_account_list_by_tag);

        listView = findViewById(R.id.recordListByTag);
        incomeTV = findViewById(R.id.accountListByTag_tagTotalIncome);
        outcomeTV = findViewById(R.id.accountListByTag_tagTotalOutcome);
        remainTV = findViewById(R.id.accountListByTag_tagTotalRemain);
        button = findViewById(R.id.accountListByTag_button);
        tagDAO = new TagDAO(ListRecordByTagActivity.this);
        recordDAO = new RecordDAO(ListRecordByTagActivity.this);

        tags = tagDAO.getTagList();
        List<String> tagString = new ArrayList<>();
        for(Tag tag: tags) tagString.add(tag.getName());

        spinner = findViewById(R.id.accountListByTag_tagSpinner);
        ArrayAdapter arrayAdapter = new ArrayAdapter(ListRecordByTagActivity.this, R.layout.support_simple_spinner_dropdown_item, tagString);
        spinner.setAdapter(arrayAdapter);

        getRecordListViewByTagId();

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                getRecordListViewByTagId();
            }
        });


        listView.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> adapterView, View view, final int i, long l) {
                AlertDialog.Builder adBuilder = new AlertDialog.Builder(ListRecordByTagActivity.this);
                adBuilder.setMessage("确认要删除记录吗？")
                        .setPositiveButton("确认", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                int recordId = records.get(i).getId();
                                recordDAO.deleteRecordById(recordId);
                                getRecordListViewByTagId();
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
                Intent intent = new Intent(ListRecordByTagActivity.this, UpdateAccountActivity.class);
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
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if(requestCode == 0x717 && resultCode == 0x717) {
            getRecordListViewByTagId();
        }
    }

    public void getRecordListViewByTagId() {
        // 获得spinner选中位置，根据位置确定选中的tag
        Tag tag = tags.get(spinner.getSelectedItemPosition());
        BigDecimal income = new BigDecimal(0);
        BigDecimal outcome = new BigDecimal(0);
        records= recordDAO.getRecordListByTagId(tag.getId());
        // 日期格式
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy/MM/dd HH:mm");
        recordsMap = new ArrayList<>();
        for(Record record: records) {
            Map<String, Object> map = new HashMap<>();
            BigDecimal count = new BigDecimal(record.getCount()).setScale(2, RoundingMode.HALF_UP);
            if (record.getType() == 0) {
                income = income.add(new BigDecimal(record.getCount()));
            } else {
                outcome = outcome.add(new BigDecimal(record.getCount()));
                count = count.multiply(new BigDecimal(-1));
            }
            map.put("tagName", tag.getName());
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

        String[] from = {"tagName", "time", "id", "type", "count"};
        int[] to = {R.id.recordItem_tagName, R.id.recordItem_createTime, R.id.recordItem_recordId, R.id.recordItem_type, R.id.recordItem_recordCount};
        SimpleAdapter simpleAdapter = new SimpleAdapter(this, recordsMap, R.layout.record_item, from, to);
        listView.setAdapter(simpleAdapter);
    }

}
