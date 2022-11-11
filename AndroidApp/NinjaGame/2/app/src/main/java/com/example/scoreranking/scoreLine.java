package com.example.scoreranking;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class scoreLine {
    private int scoreNum;
    private String scoreTime = "";

//    public scoreLine(){
//        this.scoreTime.format(DateTimeFormatter.ofPattern("uuuu-MM-dd' 'HH:mm:ss"));
//    }

    public int scoreCompare(scoreLine score2){
        if (this.scoreNum>score2.scoreNum)
            return 1;
        else if (this.scoreNum<score2.scoreNum)
            return -1;
        return 0;
    }

    public int getScoreNum(){
        return scoreNum;
    }

    public String getScoreTime(){
        return scoreTime;
    }

    public void setScoreNum(int score){
        scoreNum=score;
    }

    public void setScoreTime(String ds){
        scoreTime=ds;
    }

}
