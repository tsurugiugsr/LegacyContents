package pojo;

import mapper.NAT_Authority_Mapper;
import mapper.Vaccine_Authority_Mapper;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;

public class Vaccine_Authority {
    private String vaccineSite;
    private String password;

    public String getVaccineSite() {
        return vaccineSite;
    }

    public void setVaccineSite(String vaccineSite) {
        this.vaccineSite = vaccineSite;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public static String checkPassword(String vaccineSite, String givenPassword) throws IOException {
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession(true);

        Vaccine_Authority_Mapper vam = sqlSession.getMapper(Vaccine_Authority_Mapper.class);
        String rightPassword = vam.getPasswordByVaccineSite(vaccineSite);
        sqlSession.close();
        //System.out.println(rightPassword);
        if(givenPassword.equals(rightPassword)){
            return "True";
        } else {
            return "False";
        }
    }
}
