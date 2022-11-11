package pojo;

import mapper.NAT_Info_Mapper;
import mapper.NormalUser_Info_Mapper;
import mapper.Vaccine_Info_Mapper;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import javax.sql.rowset.spi.SyncResolver;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

public class NormalUser_Info {
    private int id;
    private String name;
    private String currentLocation;
    private String route;
    private String vaccine;
    private String badFeeling;
    private String healthCode;
    private String date;

    private String personid;

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
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

    public String getCurrentLocation() {
        return currentLocation;
    }

    public void setCurrentLocation(String currentLocation) {
        this.currentLocation = currentLocation;
    }

    public String getRoute() {
        return route;
    }

    public void setRoute(String route) {
        this.route = route;
    }

    public String getVaccine() {
        return vaccine;
    }

    public void setVaccine(String vaccine) {
        this.vaccine = vaccine;
    }

    public String getBadFeeling() {
        return badFeeling;
    }

    public void setBadFeeling(String badFeeling) {
        this.badFeeling = badFeeling;
    }

    public String getHealthCode() {
        return healthCode;
    }

    public void setHealthCode(String healthCode) {
        this.healthCode = healthCode;
    }

    public static void addNormalUserInfo(String[] info) throws IOException {
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        
        for(String str: info){
            if(str.equals("$")){
                str = "无";
            }
        }

        String name = info[1];
        String currentLocation = info[2];
        String route = info[3];
        String vaccine = info[4];
        String badFeeling = info[5];
        String healthCode = info[6];
        String date = info[7];
        
        NormalUser_Info normalUser_info = new NormalUser_Info();
        normalUser_info.setName(name);
        normalUser_info.setCurrentLocation(currentLocation);
        normalUser_info.setRoute(route);
        normalUser_info.setVaccine(vaccine);
        normalUser_info.setBadFeeling(badFeeling);
        normalUser_info.setHealthCode(healthCode);
        normalUser_info.setDate(date);

        SqlSession sqlSession = sqlSessionFactory.openSession(true);
        NormalUser_Info_Mapper normalUser_info_mapper = sqlSession.getMapper(NormalUser_Info_Mapper.class);
        normalUser_info_mapper.addNormalUserInfo(normalUser_info);

        sqlSession.close();
    }

    public static String getNormalUserInfo(String[] info) throws IOException{
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession(true);
        
        NormalUser_Info_Mapper nim = sqlSession.getMapper(NormalUser_Info_Mapper.class);
        
        String date = info[2];
        String name = info[1];
        
        NormalUser_Info ni = new NormalUser_Info();
        ni.setDate(date);
        ni.setName(name);
        
        String res = "";
        try{
            NormalUser_Info ni2 = nim.getNormalUserInfo(ni);
            res = "Y "+ni2.currentLocation+" "+ni2.route+" "+ni2.badFeeling+" "+ni2.healthCode+" "+ni2.vaccine;
        } catch (NullPointerException e){
            res = "N";
        }
        return res;
    }
}
