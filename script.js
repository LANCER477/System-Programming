const currencies = ["CZK", "USD"];
        const tableBody = document.getElementById("currencyTable");
        
        currencies.forEach(code => {
            fetch(`https://bank.gov.ua/NBUStatService/v1/statdirectory/exchangenew?json&valcode=${code}&date=20250313`)
                .then(response => response.json())
                .then(data => {
                    const currency = data[0];
                    const row = document.createElement("tr");
                    row.innerHTML = `
                        <td>${currency.exchangedate}</td>
                        <td>${currency.txt} (${currency.cc})</td>
                        <td><strong>${currency.rate.toFixed(2)}</strong></td>
                    `;
                    tableBody.appendChild(row);
                });
        });