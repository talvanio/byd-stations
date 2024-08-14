#include "../include/utils.hpp"

// Funcao que converte o formato dos endereços recebidos para uma string simples que representa o endereço da forma que ele deve 
// ser retornado ao usuário, para simplificar a classe stations e o a redabilidade do codigo em geral 
std::string adressify(std::string idend, std::string id_logrado, 
                     std::string sigla_tipo, std::string nome_logra,
                     std::string numero_imo,std::string nome_bairr,
                     std::string nome_regio,std::string cep) 
    {   
        std::string adress = std::string();
        adress.append(sigla_tipo);
        adress.append(" ");
        adress.append(nome_logra);
        adress.append(", ");    
        adress.append(numero_imo);
        adress.append(", ");
        adress.append(nome_bairr);
        adress.append(", ");
        adress.append(nome_regio);
        adress.append(", ");
        adress.append(cep);
        return adress;

    }
