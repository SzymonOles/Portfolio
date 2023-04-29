const mysql  = require('mysql2');

const db = mysql.createConnection({
    host: 'db4free.net',
    user: 'solesroot',
    password: '12345678',
    database: 'soles_db'
})

db.connect();

const getCommentsRender = (req,res) => {
    const sql = 'SELECT * FROM comments order by id desc ;';
    db.query(sql, (error, data) => {
        res.render("komentarze", {data});
    });
}

const getCommentsRenderAdmin = (req,res) => {
    const sql = 'SELECT * FROM comments order by id desc ;';
    db.query(sql, (error, data) => {
        res.render("komentarzeAdmin", {data});
    });
}

const sendComment = (req,res) => {
    let query = db.query(`INSERT INTO comments(username,comment) VALUES ("${req.body.name}","${req.body.comment}") `,(err, results) => {
        if(err) throw err;
    });
}

const delComment = (req,res) => {
    let query = db.query(`Delete from comments where id=${req.params.ID}`,(err, results) => {
        if(err) throw err;
    });
}

module.exports = {
    getCommentsRender,
    getCommentsRenderAdmin,
    sendComment,
    delComment
}