package mapper;

import pojo.Vaccine_Info;

public interface Vaccine_Info_Mapper {
    void addVaccineInfo(Vaccine_Info vi);
    void updateVaccineInfo(Vaccine_Info vi);
    int getId(Vaccine_Info vi);
    Vaccine_Info getVaccineInfoByDate(String date);
    void deleteVaccineInfo(Vaccine_Info vi);

    Vaccine_Info checkVN();

}
