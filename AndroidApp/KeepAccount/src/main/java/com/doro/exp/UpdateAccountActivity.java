package com.doro.exp;

import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.TimePicker;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.doro.exp.dao.RecordDAO;
import com.doro.exp.dao.TagDAO;
import com.doro.exp.entity.Record;
import com.doro.exp.entity.Tag;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class UpdateAccountActivity extends AppCompatActivity {
    private int id, type, tagId;
    private Double count;
    private long timeInMills;
    private String comment;
    private List<Tag> tags;
    private List<String> tagString;
    private int year, month, day, hour, minute;
    private EditText edtAmount;
    private RadioButton rbtnExpend;
    private RadioButton rbtnIncome;
    private Spinner tagSpinner;
    private EditText edtComment;
    private Button btnDate;
    private Button btnTime;
    private TagDAO tagDAO;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_account);

        //接收intent参数
        Intent intent = getIntent();
        if (intent != null) {
            Bundle bundle = intent.getExtras();
            if (bundle != null) {
                this.id = bundle.getInt("id");
                this.timeInMills = bundle.getLong("time");
                this.count = bundle.getDouble("count");
                this.type = bundle.getInt("type");
                this.tagId = bundle.getInt("tagId");
                this.comment = bundle.getString("comment");

            }
        }

        edtAmount = findViewById(R.id.addAccount_edt_amount);
        rbtnExpend = findViewById(R.id.addAccount_rbtn_expend);
        rbtnIncome = findViewById(R.id.addAccount_rbtn_income);
        tagSpinner = findViewById(R.id.addAccount_spinner);
        edtComment = findViewById(R.id.addAcount_edt_comment);
        btnDate = findViewById(R.id.addAccount_btn_date);
        btnTime = findViewById(R.id.addAccount_btn_time);
        Button btnSave = findViewById(R.id.addAccount_btn_save);

        tagDAO = new TagDAO(UpdateAccountActivity.this);
        tags = tagDAO.getTagList();
        tagString = new ArrayList<>();
        for (Tag tag : tags) tagString.add(tag.getName());
        tagString.add(new String("--新增分类--"));
        ArrayAdapter arrayAdapter = new ArrayAdapter(UpdateAccountActivity.this, R.layout.support_simple_spinner_dropdown_item, tagString);
        tagSpinner.setAdapter(arrayAdapter);

        initActivity();

        btnDate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DatePickerDialog datePickerDialog = new DatePickerDialog(btnDate.getContext(), AlertDialog.THEME_HOLO_LIGHT,
                        new DatePickerDialog.OnDateSetListener() {
                            @Override
                            public void onDateSet(DatePicker view, int y, int m, int d) {
                                UpdateAccountActivity.this.year = y;
                                UpdateAccountActivity.this.month = m + 1;
                                UpdateAccountActivity.this.day = d;
                                dateChange();
                            }
                        },
                        year, month - 1, day);
                datePickerDialog.show();
            }
        });

        btnTime.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                TimePickerDialog timePickerDialog = new TimePickerDialog(btnTime.getContext(), AlertDialog.THEME_HOLO_LIGHT, new TimePickerDialog.OnTimeSetListener() {
                    @Override
                    public void onTimeSet(TimePicker timePicker, int i, int i1) {
                        UpdateAccountActivity.this.hour = i;
                        UpdateAccountActivity.this.minute = i1;
                        timeChange();
                    }
                }, hour, minute, true);
                timePickerDialog.show();
            }
        });

        btnSave.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                boolean flag = false;
                double amount = 0;

                if (!edtAmount.getText().toString().equals("")) {
                    amount = Double.parseDouble(edtAmount.getText().toString());
                    if (amount > 0) {
                        flag = true;
                    }
                }
                if (flag) {
                    Calendar calendar = Calendar.getInstance();
                    calendar.set(year, month - 1, day, hour, minute, 0);
                    long timeInMillis = calendar.getTimeInMillis();

                    int type = 1;
                    if (rbtnIncome.isChecked()) {
                        type = 0;
                    }

                    // 获得spinner选中位置，根据位置确定选中的tag
                    Tag tag = tags.get(tagSpinner.getSelectedItemPosition());

                    Record record = new Record(id, timeInMillis,
                            Double.parseDouble(edtAmount.getText().toString()),
                            type,
                            tag.getId(),
                            edtComment.getText().toString());

                    RecordDAO recordDAO = new RecordDAO(UpdateAccountActivity.this);
                    recordDAO.updateRecord(record);

                    Toast.makeText(UpdateAccountActivity.this, "修改成功！", Toast.LENGTH_SHORT).show();

                    setResult(0x717, intent);
                    finish();
                } else {
                    Toast.makeText(UpdateAccountActivity.this, "请输入大于0的金额~", Toast.LENGTH_SHORT).show();
                }
            }
        });

        tagSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if (position != tagString.size() - 1) return;
                Intent intent1 = new Intent(UpdateAccountActivity.this, AddTagActivity.class);
                startActivityForResult(intent1, 0x716);
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == 0x716 && resultCode == 0x716) {
            tags = tagDAO.getTagList();
            tagString = new ArrayList<>();
            for (Tag tag : tags) tagString.add(tag.getName());
            tagString.add(new String("--新建分类--"));
            ArrayAdapter arrayAdapter = new ArrayAdapter(this, R.layout.support_simple_spinner_dropdown_item, tagString);
            tagSpinner.setAdapter(arrayAdapter);
        }
    }

    private void initActivity() {
        edtAmount.setText(count.toString());
        if (type == 0) {
            rbtnIncome.setChecked(true);
        } else {
            rbtnExpend.setChecked(true);
        }
        Map<Integer, Integer> tagIdMap = new HashMap<>();
        for (int i = 0; i < tags.size(); ++i) {
            tagIdMap.put(tags.get(i).getId(), i);
        }
        tagSpinner.setSelection(tagIdMap.getOrDefault(tagId, 0));
        edtComment.setText(comment);
        // 日期格式
        SimpleDateFormat dateSdf = new SimpleDateFormat("yyyy/MM/dd");
        SimpleDateFormat timeSdf = new SimpleDateFormat("HH:mm");
        String date = dateSdf.format(new Date(timeInMills));
        String time = timeSdf.format(new Date(timeInMills));

        String[] dateList = date.split("/");
        this.year = Integer.parseInt(dateList[0]);
        this.month = Integer.parseInt(dateList[1]);
        Log.i("1", dateList[1]);
        this.day = Integer.parseInt(dateList[2]);

        String[] timeList = time.split(":");
        this.hour = Integer.parseInt(timeList[0]);
        this.minute = Integer.parseInt(timeList[1]);

        dateChange();
        timeChange();
    }

    private void dateChange() {
        btnDate.setText(String.format(getResources().getString(R.string.addAccount_date), year, month, day));
    }

    private void timeChange() {
        btnTime.setText(String.format(getResources().getString(R.string.addAccount_time), hour, minute));
    }
}
