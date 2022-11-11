package pojo;

import mapper.NAT_Authority_Mapper;
import mapper.NAT_Info_Mapper;
import mapper.NormalUser_Authority_Mapper;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;

public class NormalUser_Authority {
    private String name;
    private String password;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public static String checkPassword(String name, String givenPassword) throws IOException {
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession();

        NormalUser_Authority_Mapper normalUser_authority_mapper = sqlSession.getMapper(NormalUser_Authority_Mapper.class);
        String rightPassword = normalUser_authority_mapper.selectPasswordByName(name);
        sqlSession.close();
        if(givenPassword.equals(rightPassword)){
            return "True";
        } else {
            return "False";
        }
    }

    public static void addNormalUser(String[] info) throws IOException {
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

        System.out.println(info[1]);
        System.out.println(info[2]);
        
        String name = info[1];
        String password = info[2];

        NormalUser_Authority normalUser_authority = new NormalUser_Authority();
        normalUser_authority.setName(name);
        normalUser_authority.setPassword(password);

        SqlSession sqlSession = sqlSessionFactory.openSession(true);
        NormalUser_Authority_Mapper normalUser_authority_mapper = sqlSession.getMapper(NormalUser_Authority_Mapper.class);
        normalUser_authority_mapper.addUser(normalUser_authority);

        sqlSession.close();
        
    }
}
