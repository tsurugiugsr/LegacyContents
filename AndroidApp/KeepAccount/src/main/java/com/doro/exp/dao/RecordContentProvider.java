package com.doro.exp.dao;

import android.content.ContentProvider;
import android.content.ContentUris;
import android.content.ContentValues;
import android.content.UriMatcher;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.net.Uri;

import androidx.annotation.NonNull;

public class RecordContentProvider extends ContentProvider {
    private static UriMatcher uriMatcher = new UriMatcher(-1);
    private static final int SUCCESS = 1;
    private MyDBHelper helper;
    public static final String DB_NAME = "record";

    static {
        uriMatcher.addURI("com.keepaccount.record", DB_NAME, SUCCESS);
    }

    public RecordContentProvider() {
    }

    @Override
    public boolean onCreate() {
        helper = new MyDBHelper(getContext());
        return false;
    }

    @Override
    public Uri insert(@NonNull Uri uri, ContentValues values) {
        int code = uriMatcher.match(uri);
        if (code == SUCCESS) {
            SQLiteDatabase db = helper.getWritableDatabase();
            long rowId = db.insert(DB_NAME, null, values);
            if (rowId > 0) {
                Uri insertUri = ContentUris.withAppendedId(uri, rowId);
                getContext().getContentResolver().notifyChange(insertUri, null);
                return insertUri;
            }
            db.close();
            return uri;
        } else {
            throw new UnsupportedOperationException("Not yet implemented");
        }
    }


    @Override
    public int delete(@NonNull Uri uri, String selection, String[] selectionArgs) {
        int code = uriMatcher.match(uri);
        if (code == SUCCESS) {
            SQLiteDatabase db = helper.getWritableDatabase();
            int count = db.delete(DB_NAME, selection, selectionArgs);
            if (count > 0) {
                getContext().getContentResolver().notifyChange(uri, null);
            }
            db.close();
            return count;
        } else {
            throw new UnsupportedOperationException("Not yet implemented");
        }
    }

    @Override
    public int update(@NonNull Uri uri, ContentValues values, String selection,
                      String[] selectionArgs) {
        int code = uriMatcher.match(uri);
        if (code == SUCCESS) {
            SQLiteDatabase db = helper.getWritableDatabase();
            int count = db.update(DB_NAME, values, selection, selectionArgs);
            if (count > 0) {
                getContext().getContentResolver().notifyChange(uri, null);
            }
            db.close();
            return count;
        } else {
            throw new UnsupportedOperationException("Not yet implemented");
        }
    }

    @Override
    public Cursor query(@NonNull Uri uri, String[] projection, String selection,
                        String[] selectionArgs, String sortOrder) {
        int code = uriMatcher.match(uri);
        if (code == SUCCESS) {
            SQLiteDatabase db = helper.getReadableDatabase();
            return db.query(DB_NAME, projection, selection, selectionArgs, null, null, sortOrder);
        } else {
            throw new UnsupportedOperationException("Not yet implemented");
        }
    }



    @Override
    public String getType(@NonNull Uri uri) {
        // TODO: Implement this to handle requests for the MIME type of the data
        // at the given URI.
        throw new UnsupportedOperationException("Not yet implemented");
    }
}
