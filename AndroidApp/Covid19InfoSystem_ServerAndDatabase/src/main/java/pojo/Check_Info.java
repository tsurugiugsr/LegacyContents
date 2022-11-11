package pojo;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

public class Check_Info {

    private Date currentTime;

    private String testingTime;

    private int date_gap;

    private String testeePhone;

    private String testeeName;

    public Date getCurrentTime() {
        return currentTime;
    }
    public void setCurrentTime(Date date) {
        this.currentTime = date;
    }

    public String getTestingTime() {
        return testingTime;
    }
    public void setTestingTime(String date) {
        this.testingTime = date;
    }

    public String getTesteeName() {
        return testeeName;
    }

    public void setTesteeName(String testeeName) {
        this.testeeName = testeeName;
    }
    public String getTesteePhone() {
        return testeePhone;
    }

    public void setTesteePhone(String testeePhone) {
        this.testeePhone = testeePhone;
    }

    public int getDate_gap() {
        return date_gap;
    }

    public void setDate_gap(int date_gap) {
        this.date_gap = date_gap;
    }



    public static int daydiff(Date fDate, String oDate) throws ParseException {

        Calendar aCalendar = Calendar.getInstance();

        aCalendar.setTime(fDate);

        int day1 = aCalendar.get(Calendar.DAY_OF_YEAR);
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy/MM/dd");


        aCalendar.setTime(sdf.parse(oDate));

        int day2 = aCalendar.get(Calendar.DAY_OF_YEAR);

        return day1 - day2;

    }

    public static String checkNatInfo() throws IOException, ParseException {
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession(true);

        Check_Info ci = new Check_Info();
        Date date = new Date();
        ci.setCurrentTime(date);

        List<Check_Info> list = sqlSession.selectList("mapper.Check_Info_Mapper." +
                "checkNatInfo");
        //System.out.println(list.toString());
        StringBuilder sb = new StringBuilder();
        for (Check_Info nai : list) {

            ci.date_gap = daydiff(ci.currentTime, nai.testingTime);
            if (ci.date_gap > 3) {

                sb.append(nai.testeeName).append(" ").append(nai.testeePhone).append(" ");
            }
        }
        //System.out.println("Log");
        System.out.println(sb.toString());
        return sb.toString();
    }





}
