# DeckDU v0.1

Idéias em progresso:

fazendo um parser do JSON de configuração

https://arduinojson.org/v6/api/jsonobject/begin_end/

Ainda precisa estruturar melhor, mas baseado nesse cara é possivel ir "iterando" pelo JSON, permitindo ler o arquivo como o abaixo

```
{
  "BTN_1": { "keys": ["A", "B"] },
  "BTN_2": { "keys": ["C", "D"] },
  "BTN_3": { "keys": ["E", "F"] }
}
```

Consegui ler a estrutura 

agora ao salvar, precisa limpar o arquivo antes pra dar certo