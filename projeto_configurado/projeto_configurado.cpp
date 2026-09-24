#include "App.hpp"
#include "Entrada.hpp"
#include "GradeQuadrados.hpp"

int main()
{
    const DimensoesGrade dimensoes = Entrada::lerDimensoesGrade(GradeQuadrados::DIMENSAO_MAXIMA);

    App app(dimensoes.linhas, dimensoes.colunas);
    app.run();
    return 0;
}
