import mapper.NAT_Authority_Mapper;
import mapper.NAT_Info_Mapper;
import mapper.Vaccine_Authority_Mapper;
import mapper.Vaccine_Info_Mapper;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.junit.Test;
import pojo.*;

import java.io.*;

public class ForTest {
    @Test
    public void testAddInfo() throws IOException{
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

        String inoculatorIdNum = "793740027493940271";
        String date = "2022-5-2";
        String vaccineId = "厦门生物灭活疫苗";
        String vaccineSite = "湖区疫苗注射点";

        Vaccine_Info vi = new Vaccine_Info();
        vi.setInoculatorIdNum(inoculatorIdNum);
        vi.setDate(date);
        vi.setVaccineId(vaccineId);
        vi.setVaccineSite(vaccineSite);

        SqlSession sqlSession = sqlSessionFactory.openSession(true);

        Vaccine_Info_Mapper vim = sqlSession.getMapper(Vaccine_Info_Mapper.class);
        vim.addVaccineInfo(vi);

        sqlSession.close();
    }
    
    @Test
    public void testSelectPasswordByNATSite() throws IOException{
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

        SqlSession sqlSession = sqlSessionFactory.openSession();

        NAT_Authority_Mapper nat_authority_mapper = sqlSession.getMapper(NAT_Authority_Mapper.class);
        String gotPassword = nat_authority_mapper.selectPasswordByNATSite("检测点");
        System.out.println(gotPassword);
    }
    
    
    
    @Test
    public void test2() throws IOException{
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession(true);
        
        String in = "AC 2022-05-08 田旭泽";
        String[] info = in.split(" ");
        
        String res = NormalUser_Info.getNormalUserInfo(info);
        System.out.println(res);
        sqlSession.close();
    }
}
