package com.example.zhang.keepaccount.dao;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.util.Log;

import com.example.zhang.keepaccount.entity.Record;
import com.example.zhang.keepaccount.entity.Tag;

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

    public Uri saveTag(Tag tag) {
        values = new ContentValues();
        values.put("name", tag.getName());
        values.put("type", tag.getType());
        Uri newUri = resolver.insert(uri, values);
        Log.i("log:", "add new tag:" + newUri);
        return newUri;
    }

    public List<Tag> getTagList() {
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

    public int deleteRecordById(int id) {
        String[] args = new String[] {String.valueOf(id)};
        int deleteCount = resolver.delete(uri, "id = ?", args);
        Log.i("log:", "delete: " + id);
        return deleteCount;
    }
}
