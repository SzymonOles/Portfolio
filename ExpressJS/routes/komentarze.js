var express = require('express');
var router = express.Router();

const komentarzeController = require('../controllers/komentarzeController');
const {sendComment, delComment} = require("../controllers/komentarzeController");


// /komentarze/
router.get('/', komentarzeController.getCommentsRender);

// /komentarze/send
router.post('/send',async (req, res) => {
    await komentarzeController.sendComment(req);
    res.redirect("/komentarze");
});

// /komentarze/admin
router.get('/admin', komentarzeController.getCommentsRenderAdmin);

// /komentarze/admin/del/id
router.get('/admin/del/:ID',async (req, res) => {
    await komentarzeController.delComment(req);
    res.redirect("/komentarze/admin");
});

module.exports = router;
