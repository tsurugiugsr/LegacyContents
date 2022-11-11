package com.doro.exp.entity;

/**
 * Created by zhang on 2022/4/17.
 */

public class Tag {
    private int id;
    private String name;
    // 0-收入 1-支出
    private int type;
    private int deleted;

    public Tag() {
    }

    public Tag(int id, String name, int type) {
        this.id = id;
        this.name = name;
        this.type = type;
    }

    public Tag(String name, int type, int deleted) {
        this.name = name;
        this.type = type;
        this.deleted = deleted;
    }

    public Tag(int id, String name, int type, int deleted) {
        this.id = id;
        this.name = name;
        this.type = type;
        this.deleted = deleted;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public int getDeleted() {
        return deleted;
    }

    public void setDeleted(int deleted) {
        this.deleted = deleted;
    }

    @Override
    public String toString() {
        return "Tag{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", type=" + type +
                '}';
    }
}
