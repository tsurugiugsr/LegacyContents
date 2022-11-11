package com.example.zhang.keepaccount.dao;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

/**
 * Created by zhang on 2022/4/17.
 */

class MyDBHelper extends SQLiteOpenHelper {
    MyDBHelper(Context context) {
        super(context, "account.db", null, 1);
    }

    @Override
    public void onCreate(SQLiteDatabase sqLiteDatabase) {
        sqLiteDatabase.execSQL("CREATE TABLE `record`  (\n" +
                "  `id` integer primary key autoincrement,\n" +
                "  `time` bigint,\n" +
                "  `count` double,\n" +
                "  `type` integer,\n" +
                "  `tag_id` integer,\n" +
                "  `comment` varchar(100)\n" +
                ")");
        sqLiteDatabase.execSQL("CREATE TABLE `tag`  (\n" +
                "  `id` integer primary key autoincrement,\n" +
                "  `name` varchar(10),\n" +
                "  `type` integer\n" +
                ")");
    }

    @Override
    public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1) {

    }
}
