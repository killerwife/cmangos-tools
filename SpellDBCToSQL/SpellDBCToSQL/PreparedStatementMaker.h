#include <string>
class PreparedStatementMaker
{
public:
    PreparedStatementMaker();
    ~PreparedStatementMaker();
    void MakePreparedStatement(std::string filename, std::string& output);
};

