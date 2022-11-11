package com.example.zhang.keepaccount.dao;

import android.content.ContentResolver;
import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.util.Log;

import com.example.zhang.keepaccount.entity.Record;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by zhang on 2022/4/21.
 */

public class RecordDAO {

    private ContentResolver resolver;
    private Uri uri;
    private ContentValues values;

    public RecordDAO(Context context) {
        this.resolver = context.getContentResolver();
        this.uri = Uri.parse("content://com.keepaccount.record/record");
    }

    public Uri saveRecord(Record record) {
        values = new ContentValues();
        values.put("time", record.getTime());
        values.put("count", record.getCount());
        values.put("type", record.getType());
        values.put("tag_id", record.getTagId());
        values.put("comment", record.getComment());
        Uri newUri = resolver.insert(uri, values);
        Log.i("log:", "add new record:" + newUri);
        return newUri;
    }

    public int updateRecord(Record record) {
        values = new ContentValues();
        values.put("time", record.getTime());
        values.put("count", record.getCount());
        values.put("type", record.getType());
        values.put("tag_id", record.getTagId());
        values.put("comment", record.getComment());
        int updateCount = resolver.update(uri, values, "id=?", new String[]{String.valueOf(record.getId())});
        Log.i("log:", "update " + updateCount + " records");
        return updateCount;
    }

    public double getIncomeByStartTimeAndEndTime(long startTime, long endTime) {
        String[] columns = new String[] {"count"};
        String[] args = new String[] {String.valueOf(startTime), String.valueOf(endTime)};
        Cursor cursor = resolver.query(uri, columns, "time > ? and time < ? and type = 0", args, null);
        double ans = 0;
        while(cursor.moveToNext()) {
            ans += cursor.getDouble(0);
        }
        cursor.close();
        Log.i("log:", "getIncome: " + ans);
        return ans;
    }

    public double getOutcomeByStartTimeAndEndTime(long startTime, long endTime) {
        String[] columns = new String[] {"count"};
        String[] args = new String[] {String.valueOf(startTime), String.valueOf(endTime)};
        Cursor cursor = resolver.query(uri, columns, "time > ? and time < ? and type = 1", args, null);
        double ans = 0;
        while(cursor.moveToNext()) {
            ans += cursor.getDouble(0);
        }
        cursor.close();
        Log.i("log:", "getOutcome: " + ans);
        return ans;
    }

    public List<Record> getRecordListByStartTimeAndEndTime(long startTime, long endTime) {
        String[] columns = new String[] {"id", "time", "count", "type", "tag_id", "comment"};
        String[] args = new String[] {String.valueOf(startTime), String.valueOf(endTime)};
        Cursor cursor = resolver.query(uri, columns, "time > ? and time < ?", args, "time desc");
        List<Record> records = new ArrayList<>();
        while(cursor.moveToNext()) {
            int id = cursor.getInt(0);
            long time = cursor.getLong(1);
            double count = cursor.getDouble(2);
            int type = cursor.getInt(3);
            int tagId = cursor.getInt(4);
            String comment = cursor.getString(5);
            Record record = new Record(id, time, count, type, tagId, comment);
            records.add(record);
        }
        cursor.close();
        return records;
    }

    public List<Record> getRecordListByTagId(int tagId) {
        String[] columns = new String[] {"id", "time", "count", "type", "comment"};
        String[] args = new String[] {String.valueOf(tagId)};
        Cursor cursor = resolver.query(uri, columns, "tag_id = ?", args, "time desc");
        List<Record> records = new ArrayList<>();
        while(cursor.moveToNext()) {
            int id = cursor.getInt(0);
            long time = cursor.getLong(1);
            double count = cursor.getDouble(2);
            int type = cursor.getInt(3);
            String comment = cursor.getString(4);
            Record record = new Record(id, time, count, type, tagId, comment);
            records.add(record);
        }
        cursor.close();
        return records;
    }

    public int deleteRecordById(int id) {
        String[] args = new String[] {String.valueOf(id)};
        int deleteCount = resolver.delete(uri, "id = ?", args);
        Log.i("log:", "delete: " + id);
        return deleteCount;
    }
}
