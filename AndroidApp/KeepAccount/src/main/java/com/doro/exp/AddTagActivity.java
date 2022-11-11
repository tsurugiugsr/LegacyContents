package com.doro.exp;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.Toast;

import com.doro.exp.dao.TagDAO;
import com.doro.exp.entity.Tag;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class AddTagActivity extends Activity {

    private EditText tagInput;
    private ListView tagList;

    private TagDAO tagDAO;
    private List<Tag> tags;
    private List<Map<String, Object>> tagsMap;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_tag);

        tagInput = findViewById(R.id.addTag_tagInput);
        tagList = findViewById(R.id.addTag_tagList);

        tagListUpdate();

        tagList.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> adapterView, View view, int i, long l) {
                AlertDialog.Builder adBuilder = new AlertDialog.Builder(AddTagActivity.this);
                adBuilder.setMessage("确认要删除分类吗？")
                        .setPositiveButton("确认", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                int recordId = tags.get(i).getId();
                                tagDAO.deleteRecordById(recordId);
                                tagListUpdate();
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

    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        if (keyCode == KeyEvent.KEYCODE_BACK) {
            Intent intent = getIntent();
            setResult(0x716, intent);
            finish();
        }
        return super.onKeyDown(keyCode, event);
    }

    public void tagListUpdate() {
        tagDAO = new TagDAO(AddTagActivity.this);
        tags = tagDAO.getTagList();
        tagsMap = new ArrayList<>();
        for (Tag tag : tags) {
            Map<String, Object> map = new HashMap<>();
            map.put("tagName", tag.getName());
            map.put("tagID", tag.getId());
            map.put("tagType", tag.getType());
            tagsMap.add(map);
        }
        String[] from = {"tagName", "tagID", "tagType"};
        int[] to = {R.id.tagItem_tagName, R.id.tagItem_tagID, R.id.tagItem_tagType};
        SimpleAdapter simpleAdapter = new SimpleAdapter(this, tagsMap, R.layout.tag_item, from, to);
        tagList.setAdapter(simpleAdapter);
    }

    public void addTag(View view) {
        Tag tag = new Tag(tagInput.getText().toString(), 1, 0);
        if (tagDAO.saveTag(tag)) {
            Toast.makeText(this, "添加成功", Toast.LENGTH_SHORT).show();
        } else {
            Toast.makeText(this, "已有重复项", Toast.LENGTH_SHORT).show();
        }
        tagListUpdate();
    }
}