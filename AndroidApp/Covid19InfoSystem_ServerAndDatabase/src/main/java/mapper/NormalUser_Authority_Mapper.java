package mapper;

import pojo.NormalUser_Authority;

public interface NormalUser_Authority_Mapper {
    void addUser(NormalUser_Authority normalUser_authority);
    String selectPasswordByName(String name);
}
