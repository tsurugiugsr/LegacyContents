package com.example.zhang.keepaccount.entity;

/**
 * Created by zhang on 2022/4/17.
 */

public class Record {
    private int id;
    private long time;
    private double count;
    // 0-收入 1-支出
    private int type;
    private int tagId;
    private String comment;

    public Record() {
    }

    public Record(long time, double count, int type, int tagId, String comment) {
        this.time = time;
        this.count = count;
        this.type = type;
        this.tagId = tagId;
        this.comment = comment;
    }

    public Record(int id, long time, double count, int type, int tagId, String comment) {
        this.id = id;
        this.time = time;
        this.count = count;
        this.type = type;
        this.tagId = tagId;
        this.comment = comment;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public long getTime() {
        return time;
    }

    public void setTime(long time) {
        this.time = time;
    }

    public double getCount() {
        return count;
    }

    public void setCount(double count) {
        this.count = count;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public int getTagId() {
        return tagId;
    }

    public void setTagId(int tagId) {
        this.tagId = tagId;
    }

    public String getComment() {
        return comment;
    }

    public void setComment(String comment) {
        this.comment = comment;
    }

    @Override
    public String toString() {
        return "Record{" +
                "id=" + id +
                ", time=" + time +
                ", count=" + count +
                ", type=" + type +
                ", tagId=" + tagId +
                ", comment='" + comment + '\'' +
                '}';
    }
}
