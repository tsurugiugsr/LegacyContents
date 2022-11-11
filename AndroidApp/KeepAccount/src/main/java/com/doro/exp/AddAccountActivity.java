package com.doro.exp;

import android.app.AlertDialog;
import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.content.ContentResolver;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.text.InputFilter;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.Spinner;
import android.widget.TimePicker;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.doro.exp.dao.TagDAO;
import com.doro.exp.entity.Record;
import com.doro.exp.dao.RecordDAO;
import com.doro.exp.entity.Tag;
import com.doro.exp.util.AmountFilter;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;


public class AddAccountActivity extends AppCompatActivity {
    private EditText edtAmount;
    private RadioButton rbtnIncome;
    private List<Tag> tags;
    private List<String> tagString;
    private Spinner tagSpinner;
    private EditText edtComment;
    private int year, month, day, hour, minute;
    private Button btnDate;
    private Button btnTime;
    private TagDAO tagDAO;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_account);

        edtAmount = findViewById(R.id.addAccount_edt_amount);
        rbtnIncome = findViewById(R.id.addAccount_rbtn_income);
        tagSpinner = findViewById(R.id.addAccount_spinner);
        edtComment = findViewById(R.id.addAcount_edt_comment);
        btnDate = findViewById(R.id.addAccount_btn_date);
        btnTime = findViewById(R.id.addAccount_btn_time);
        Button btnSave = findViewById(R.id.addAccount_btn_save);

        tagDAO = new TagDAO(AddAccountActivity.this);
        tags = tagDAO.getTagList();
        tagString = new ArrayList<>();
        for (Tag tag : tags) tagString.add(tag.getName());
        tagString.add(new String("--新建分类--"));

        ArrayAdapter arrayAdapter = new ArrayAdapter(AddAccountActivity.this, R.layout.support_simple_spinner_dropdown_item, tagString);
        tagSpinner.setAdapter(arrayAdapter);


        edtAmount.setCursorVisible(false);
        edtAmount.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                edtAmount.setSelection(edtAmount.getText().length());
            }
        });
        InputFilter[] filters = {new AmountFilter()};
        edtAmount.setFilters(filters);

        Calendar c = Calendar.getInstance();
        year = c.get(Calendar.YEAR);
        month = c.get(Calendar.MONTH) + 1;
        day = c.get(Calendar.DAY_OF_MONTH);
        hour = c.get(Calendar.HOUR_OF_DAY);
        minute = c.get(Calendar.MINUTE);
        dateChange();
        timeChange();// 初始化时间

        btnDate.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                DatePickerDialog datePickerDialog = new DatePickerDialog(btnDate.getContext(), AlertDialog.THEME_HOLO_LIGHT,
                        new DatePickerDialog.OnDateSetListener() {
                            @Override
                            public void onDateSet(DatePicker view, int y, int m, int d) {
                                AddAccountActivity.this.year = y;
                                AddAccountActivity.this.month = m + 1;
                                AddAccountActivity.this.day = d;
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
                        AddAccountActivity.this.hour = i;
                        AddAccountActivity.this.minute = i1;
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

                    Record record = new Record(timeInMillis,
                            amount,
                            type,
                            tag.getId(),
                            edtComment.getText().toString());

                    RecordDAO recordDAO = new RecordDAO(AddAccountActivity.this);
                    recordDAO.saveRecord(record);

                    Toast.makeText(AddAccountActivity.this, "添加成功！", Toast.LENGTH_SHORT).show();
                    Intent intent = getIntent();
                    setResult(0x715, intent);
                    finish();
                } else {
                    Toast.makeText(AddAccountActivity.this, "请输入大于0的金额~", Toast.LENGTH_SHORT).show();
                }
            }
        });

        tagSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if (position != tagString.size() - 1) return;
                Intent intent1 = new Intent(AddAccountActivity.this, AddTagActivity.class);
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

    private void dateChange() {
        btnDate.setText(String.format(getResources().getString(R.string.addAccount_date), year, month, day));
    }

    private void timeChange() {
        btnTime.setText(String.format(getResources().getString(R.string.addAccount_time), hour, minute));
    }

}
