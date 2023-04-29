const mysql  = require('mysql2');

const db = mysql.createConnection({
    host: 'db4free.net',
    user: 'solesroot',
    password: '12345678',
    database: 'soles_db'
})

db.connect();

const getMain = (req,res) => {
    const sql = 'SELECT * FROM mats;';
    db.query(sql, (error, data) => {
        res.render("katalog", {data});
    });
}

module.exports = {
    getMain
}