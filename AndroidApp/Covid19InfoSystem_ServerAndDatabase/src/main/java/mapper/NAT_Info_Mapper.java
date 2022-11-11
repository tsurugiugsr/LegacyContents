package mapper;

import pojo.NAT_Info;

import java.util.ArrayList;

public interface NAT_Info_Mapper {
    void addNATInfo(NAT_Info nat_info);
    NAT_Info getNATInfo(String testeeName);
}
