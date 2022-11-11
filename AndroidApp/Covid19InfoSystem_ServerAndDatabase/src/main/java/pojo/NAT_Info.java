package pojo;

import mapper.NAT_Authority_Mapper;
import mapper.NAT_Info_Mapper;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;

public class NAT_Info {
    private String testeeIdNum;
    private String testeeName;
    private String testeePhone;
    private String testingTime;
    private String testingResult;
    private String natSite;

    public String getTesteeIdNum() {
        return testeeIdNum;
    }

    public void setTesteeIdNum(String testeeIdNum) {
        this.testeeIdNum = testeeIdNum;
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

    public String getTestingTime() {
        return testingTime;
    }

    public void setTestingTime(String testingTime) {
        this.testingTime = testingTime;
    }

    public String getTestingResult() {
        return testingResult;
    }

    public void setTestingResult(String testingResult) {
        this.testingResult = testingResult;
    }

    public String getNatSite() {
        return natSite;
    }

    public void setNatSite(String natSite) {
        this.natSite = natSite;
    }

    public static void addNATInfo(String[] info) throws IOException {
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

        String testeeIdNum = info[1];
        String testeeName = info[2];
        String testeePhone = info[3];
        String testingTime = info[4];
        String testingResult = info[5];
        String natSite = info[6];
        
        NAT_Info nat_info = new NAT_Info();
        nat_info.setTesteeIdNum(testeeIdNum);
        nat_info.setTesteeName(testeeName);
        nat_info.setTesteePhone(testeePhone);
        nat_info.setTestingTime(testingTime);
        nat_info.setTestingResult(testingResult);
        nat_info.setNatSite(natSite);

        SqlSession sqlSession = sqlSessionFactory.openSession(true);
        NAT_Info_Mapper nat_info_mapper = sqlSession.getMapper(NAT_Info_Mapper.class);
        nat_info_mapper.addNATInfo(nat_info);
        sqlSession.close();
    }

    public static String getNATInfo(String testeeName) throws IOException {
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession(true);

        List<NAT_Info> list = sqlSession.selectList("mapper.NAT_Info_Mapper." +
                "getNATInfo", testeeName);
        StringBuilder sb = new StringBuilder();
        for(NAT_Info nai: list){
            sb.append(nai.testingTime).append(" ").append(nai.natSite).append(" ").append(nai.testingResult)
                    .append(" ");
        }
        return sb.toString();
    }
}
