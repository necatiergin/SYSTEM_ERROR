#include <system_error>
#include <iostream>

struct MyCategory : std::error_category  {
    const char* name() const noexcept override 
    {
        return "mycat"; 
    }
    
    std::string message(int ev) const override 
    {
        switch (ev) {
        case 1: return "Something failed";
        case 2: return "Resource busy";
        default: return "Unknown";
    }
    }
};

const MyCategory& my_category() 
{
    static MyCategory c;
    return c;
}

int main() 
{
    std::error_code ec(2, my_category());
    std::cout << "Error: " << ec.message() << '\n';  // Output: Resource busy
}
