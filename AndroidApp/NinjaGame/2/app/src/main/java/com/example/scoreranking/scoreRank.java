package com.example.scoreranking;

import static android.view.View.SYSTEM_UI_FLAG_FULLSCREEN;
import static android.view.View.SYSTEM_UI_FLAG_HIDE_NAVIGATION;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.os.Environment;
import android.preference.PreferenceManager;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class scoreRank extends AppCompatActivity {

    private int scoreCount=0;
    private scoreLine[] scoreHistories = new scoreLine[11];

    public scoreRank(){
        Log.i("TouyaDebuging", "scoreRank: scoreRank()");
        for (int i = 0;i<11;i++){
            scoreHistories[i]=new scoreLine();
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.i("TouyaDebuging", "scoreRank: onCreate()");
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_score_rank);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
        getSupportActionBar().hide();
        View decorView = getWindow().getDecorView();
        decorView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY+SYSTEM_UI_FLAG_FULLSCREEN+SYSTEM_UI_FLAG_HIDE_NAVIGATION);

        scoreDisplay();
    }

    public void scoreAdd(int scoreNew){
        LocalDateTime newNow = LocalDateTime.now();
        Log.i("TouyaDebuging", "scoreRank: scoreAdd()"+scoreNew);
        scoreHistories[scoreCount].setScoreNum(scoreNew);
        scoreHistories[scoreCount].setScoreTime(newNow.format(DateTimeFormatter.ofPattern("uuuu-MM-dd' 'HH:mm:ss")));
        scoreCount++;
        scoreRanking();
        try {
            scoreStore();
        } catch (Exception e) {
            Log.i("TouyaDebuging", "scoreRank: scoreAdd()Bug");
            e.printStackTrace();
        }
    }

    public void scoreDisplay(){
        scoreCount=0;
        for (int i = 0;i<11;i++){
            scoreHistories[i]=new scoreLine();
        }
        Log.i("TouyaDebuging", "scoreRank: scoreDisplay()");
        try {
            scoreRead();
        } catch (IOException e) {
            e.printStackTrace();
        }
        TextView ts = (TextView) findViewById(R.id.textView12);
        TextView td = (TextView) findViewById(R.id.textView13);
        if (scoreHistories[0].getScoreNum()!=0){
            ts = (TextView) findViewById(R.id.textView12);
            td = (TextView) findViewById(R.id.textView13);
            ts.setText("\t得分："+scoreHistories[0].getScoreNum());
            td.setText("\t时间："+scoreHistories[0].getScoreTime());
            Log.i("TouyaDebuging", "scoreRank: scoreDisplay()"+ts.getText().toString()+"  "+td.getText().toString());
        }
        if (scoreHistories[1].getScoreNum()!=0){
            ts = (TextView) findViewById(R.id.textView22);
            td = (TextView) findViewById(R.id.textView23);
            ts.setText("\t得分："+scoreHistories[1].getScoreNum());
            td.setText("\t时间："+scoreHistories[1].getScoreTime());
            Log.i("TouyaDebuging", "scoreRank: scoreDisplay()"+ts.getText().toString()+"  "+td.getText().toString());
        }
        if (scoreHistories[2].getScoreNum()!=0){
            ts = (TextView) findViewById(R.id.textView32);
            td = (TextView) findViewById(R.id.textView33);
            ts.setText("\t得分："+scoreHistories[2].getScoreNum());
            td.setText("\t时间："+scoreHistories[2].getScoreTime());
            Log.i("TouyaDebuging", "scoreRank: scoreDisplay()"+ts.getText().toString()+"  "+td.getText().toString());
        }
        if (scoreHistories[3].getScoreNum()!=0){
            ts = (TextView) findViewById(R.id.textView42);
            td = (TextView) findViewById(R.id.textView43);
            ts.setText("\t得分："+scoreHistories[3].getScoreNum());
            td.setText("\t时间："+scoreHistories[3].getScoreTime());
            Log.i("TouyaDebuging", "scoreRank: scoreDisplay()"+ts.getText().toString()+"  "+td.getText().toString());
        }
        if (scoreHistories[4].getScoreNum()!=0){
            ts = (TextView) findViewById(R.id.textView52);
            td = (TextView) findViewById(R.id.textView53);
            ts.setText("\t得分："+scoreHistories[4].getScoreNum());
            td.setText("\t时间："+scoreHistories[4].getScoreTime());
            Log.i("TouyaDebuging", "scoreRank: scoreDisplay()"+ts.getText().toString()+"  "+td.getText().toString());
        }
        if (scoreHistories[5].getScoreNum()!=0){
            ts = (TextView) findViewById(R.id.textView62);
            td = (TextView) findViewById(R.id.textView63);
            ts.setText("\t得分："+scoreHistories[5].getScoreNum());
            td.setText("\t时间："+scoreHistories[5].getScoreTime());
            Log.i("TouyaDebuging", "scoreRank: scoreDisplay()"+ts.getText().toString()+"  "+td.getText().toString());
        }
        if (scoreHistories[6].getScoreNum()!=0){
            ts = (TextView) findViewById(R.id.textView72);
            td = (TextView) findViewById(R.id.textView73);
            ts.setText("\t得分："+scoreHistories[6].getScoreNum());
            td.setText("\t时间："+scoreHistories[6].getScoreTime());
            Log.i("TouyaDebuging", "scoreRank: scoreDisplay()"+ts.getText().toString()+"  "+td.getText().toString());
        }
        if (scoreHistories[7].getScoreNum()!=0){
            ts = (TextView) findViewById(R.id.textView82);
            td = (TextView) findViewById(R.id.textView83);
            ts.setText("\t得分："+scoreHistories[7].getScoreNum());
            td.setText("\t时间："+scoreHistories[7].getScoreTime());
            Log.i("TouyaDebuging", "scoreRank: scoreDisplay()"+ts.getText().toString()+"  "+td.getText().toString());
        }
        if (scoreHistories[8].getScoreNum()!=0){
            ts = (TextView) findViewById(R.id.textView92);
            td = (TextView) findViewById(R.id.textView93);
            ts.setText("\t得分："+scoreHistories[8].getScoreNum());
            td.setText("\t时间："+scoreHistories[8].getScoreTime());
            Log.i("TouyaDebuging", "scoreRank: scoreDisplay()"+ts.getText().toString()+"  "+td.getText().toString());
        }
        if (scoreHistories[9].getScoreNum()!=0){
            ts = (TextView) findViewById(R.id.textView102);
            td = (TextView) findViewById(R.id.textView103);
            ts.setText("\t得分："+scoreHistories[9].getScoreNum());
            td.setText("\t时间："+scoreHistories[9].getScoreTime());
            Log.i("TouyaDebuging", "scoreRank: scoreDisplay()"+ts.getText().toString()+"  "+td.getText().toString());
        }
    }

    public void scoreStore() throws Exception {

        String outS="";
        for(int i=0;i<scoreCount;i++){
            outS+=scoreHistories[i].getScoreNum()+"x"+scoreHistories[i].getScoreTime()+"d";
        }
        FileIO.fout(this,outS);
        Log.i("TouyaDebuging", "scoreRank: scoreStore()"+outS+scoreCount);
    }

    public void scoreRead() throws IOException {
        Log.i("TouyaDebuging", "scoreRank: scoreRead()Start"+scoreCount);

        String ss = FileIO.fint(this,"data.txt");
        Log.i("TouyaDebuging", "scoreRank: scoreRead()Start"+ss);
        String [] data = ss.split("d");

        for (int i = 0;i<data.length-1;i++){
           {
               Log.i("TouyaDebuging", "scoreRank: scoreRead()Start"+data[i]);
                scoreCount++;
                scoreHistories[i].setScoreNum(Integer.parseInt(data[i].split("x")[0]));
                if (Integer.parseInt(data[i].split("x")[0]) != 0) {
                    scoreHistories[i].setScoreTime(data[i].split("x")[1]);
                }
           }
        }
    }

    public void scoreRanking(){
        Log.i("TouyaDebuging", "scoreRank: scoreRanking()");
        scoreLine tempSL = new scoreLine();
        LocalDateTime newLDT = null;

        for (int i = 0;i<scoreCount;i++){
            for (int j = 0;j<scoreCount-1;j++){
                if (scoreHistories[j].scoreCompare(scoreHistories[j+1])==-1){
                    tempSL.setScoreNum(scoreHistories[j].getScoreNum());
                    tempSL.setScoreTime(scoreHistories[j+1].getScoreTime().toString());
                    scoreHistories[j].setScoreNum(scoreHistories[j+1].getScoreNum());
                    scoreHistories[j].setScoreTime(scoreHistories[j+1].getScoreTime().toString());
                    scoreHistories[j+1].setScoreNum(tempSL.getScoreNum());
                    scoreHistories[j+1].setScoreTime(tempSL.getScoreTime().toString());
                }
            }
        }
        if (scoreCount>10)
            scoreCount=10;
    }

    @Override
    public void finish() {
        super.finish();
        overridePendingTransition(0,0);
    }
}