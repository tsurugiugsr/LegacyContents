package pojo;

import mapper.NAT_Info_Mapper;
import mapper.Vaccine_Info_Mapper;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

public class Vaccine_Info {
    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
    }

    private int count;
    private int id;
    private String inoculatorIdNum;
    private String vaccineId;
    private String date;
    private String vaccineSite;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getInoculatorIdNum() {
        return inoculatorIdNum;
    }

    public void setInoculatorIdNum(String inoculatorIdNum) {
        this.inoculatorIdNum = inoculatorIdNum;
    }

    public String getVaccineId() {
        return vaccineId;
    }

    public void setVaccineId(String vaccineId) {
        this.vaccineId = vaccineId;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getVaccineSite() {
        return vaccineSite;
    }

    public void setVaccineSite(String vaccineSite) {
        this.vaccineSite = vaccineSite;
    }

    public static void addVaccineInfo(String[] info) throws IOException {
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

        String inoculatorIdNum = info[1];
        String vaccineId = info[3];
        String date = info[2];
        String vaccineSite = info[4];
        
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

    public static void updateVaccineInfo(int id, String[] info) throws IOException {
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

        SqlSession sqlSession = sqlSessionFactory.openSession(true); //关闭事务，自动提交

        Vaccine_Info vi = new Vaccine_Info();
        vi.setId(id);
        vi.setInoculatorIdNum(info[5]);
        vi.setDate(info[6]);
        vi.setVaccineId(info[7]);
        vi.setVaccineSite(info[8]);
        
        Vaccine_Info_Mapper vim = sqlSession.getMapper(Vaccine_Info_Mapper.class);
        vim.updateVaccineInfo(vi);
        sqlSession.close();
    }
    
    public static int getOriginalId(String[] info) throws IOException{
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession(true);
        
        Vaccine_Info vi = new Vaccine_Info();
        vi.setInoculatorIdNum(info[1]);
        vi.setDate(info[2]);
        vi.setVaccineId(info[3]);
        vi.setVaccineSite(info[4]);
        
        Vaccine_Info_Mapper vim = sqlSession.getMapper(Vaccine_Info_Mapper.class);
        return vim.getId(vi);
    }

    public static String getVaccineInfoByDate(String[] info) throws IOException{
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession(true);
        
        Vaccine_Info_Mapper vim = sqlSession.getMapper(Vaccine_Info_Mapper.class);
        Vaccine_Info vi = vim.getVaccineInfoByDate(info[1]);
        sqlSession.close();
        return vi.inoculatorIdNum+" "+vi.date+" "+vi.vaccineId+" "+vi.vaccineSite;
    }

    public static void deleteVaccineInfo(String[] info) throws IOException{
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession(true);

        Vaccine_Info vi = new Vaccine_Info();
        vi.setInoculatorIdNum(info[1]);
        vi.setDate(info[2]);
        vi.setVaccineId(info[3]);
        vi.setVaccineSite(info[4]);

        Vaccine_Info_Mapper vim = sqlSession.getMapper(Vaccine_Info_Mapper.class);
        vim.deleteVaccineInfo(vi);
        sqlSession.close();
    }

    public static String checkVN() throws IOException{
        String resourse = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resourse);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        SqlSession sqlSession = sqlSessionFactory.openSession(true);



        List<Vaccine_Info> list = sqlSession.selectList("mapper.Vaccine_Info_Mapper." +
                "checkVN");

        StringBuilder sb = new StringBuilder();
        for (Vaccine_Info nai : list) {

            if (nai.getCount()< 3) {
                sb.append(nai.getInoculatorIdNum()).append(" ").append(nai.getCount()).append(" ");
            }
        }

        return sb.toString();
    }
}
