//
// Created by sqks on 2026/2/13.
//

#include "MyTest.h"
#include "person.pb.h"

void MyTest::test() {
    // 创建对象
    Person p;

    // 设置数据
    p.set_name("Alice");
    p.set_age(18);

    // ===== 序列化 =====
    std::string data;
    p.SerializeToString(&data);

    std::cout << "序列化后数据长度: " << data.size() << std::endl;

    // ===== 反序列化 =====
    Person p2;
    p2.ParseFromString(data);

    std::cout << "name: " << p2.name() << std::endl;
    std::cout << "age: " << p2.age() << std::endl;

    return;
}