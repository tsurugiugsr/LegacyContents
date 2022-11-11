package pojo;

import mapper.NAT_Authority_Mapper;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;

public class NAT_Authority {
    private String natSite;
    private String password;

    public String getNatSite() {
        return natSite;
    }

    public String getPassword() {
        return password;
    }

    public void setNatSite(String natSite) {
        this.natSite = natSite;
    }

    public void setPassword(String password) {
        this.password = password;
    }
    
    public static String checkPassword(String natSite, String givenPassword) throws IOException {
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession(true);

        NAT_Authority_Mapper nat_authority_mapper = sqlSession.getMapper(NAT_Authority_Mapper.class);
        String rightPassword = nat_authority_mapper.selectPasswordByNATSite(natSite);
        sqlSession.close();
        if(givenPassword.equals(rightPassword)){
            return "True";
        } else {
            return "False";
        }
    }
}
