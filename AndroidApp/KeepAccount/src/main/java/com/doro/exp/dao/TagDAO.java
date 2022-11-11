package com.doro.exp.dao;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.util.Log;

import com.doro.exp.entity.Tag;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by zhang on 2022/4/21.
 */

public class TagDAO {
    private ContentResolver resolver;
    private Uri uri;
    private ContentValues values;

    public TagDAO(Context context) {
        this.resolver = context.getContentResolver();
        this.uri = Uri.parse("content://com.keepaccount.tag/tag");
    }

    public boolean saveTag(Tag tag) {
        values = new ContentValues();
        List<Tag> tags = getAllTagList();
        for(Tag tag1: tags) {
            if(tag1.getName().endsWith(tag.getName())) {
                return false;
            }
        }
        values.put("name", tag.getName());
        values.put("type", tag.getType());
        values.put("deleted", 0);
        Uri newUri = resolver.insert(uri, values);
        Log.i("log:", "add new tag:" + newUri);
        return true;
    }

    public List<Tag> getAllTagList() {
        String[] columns = new String[] {"id", "name", "type"};
        Cursor cursor = resolver.query(uri, columns, null, null, null);
        List<Tag> tags = new ArrayList<>();
        while(cursor.moveToNext()) {
            int id = cursor.getInt(0);
            String name = cursor.getString(1);
            int type = cursor.getInt(2);
            Tag tag = new Tag(id, name, type);
            tags.add(tag);
        }
        cursor.close();
        return tags;
    }

    public List<Tag> getTagList() {
        String[] columns = new String[] {"id", "name", "type"};
        Cursor cursor = resolver.query(uri, columns, "deleted = 0", null, null);
        List<Tag> tags = new ArrayList<>();
        while(cursor.moveToNext()) {
            int id = cursor.getInt(0);
            String name = cursor.getString(1);
            int type = cursor.getInt(2);
            Tag tag = new Tag(id, name, type);
            tags.add(tag);
        }
        cursor.close();
        return tags;
    }

    public int deleteRecordById(int id) {
        values = new ContentValues();
        values.put("deleted", 1);
        int updateCount = resolver.update(uri, values, "id = ?", new String[]{String.valueOf(id)});
        Log.i("log:", "delete: " + id);
        return 1;
    }
}
