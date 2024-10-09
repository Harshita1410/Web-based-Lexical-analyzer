from flask import Flask, request, render_template
import os
from pygments import highlight
from pygments.lexers import CLexer, PythonLexer
from pygments.formatters import HtmlFormatter

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = './uploads'

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/upload', methods=['POST'])
def upload_file():
    if 'file' not in request.files:
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        return 'No selected file'
    if file:
        # Save the uploaded file
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
        file.save(filepath)
        
        # Read the file content
        with open(filepath, 'r') as f:
            source_code = f.read()

        # Perform lexical analysis
        tokens, highlighted_code = lexical_analyze(source_code, filepath)
        
        # Render the result template with source code and tokens
        return render_template('result.html', source_code=highlighted_code, tokens=tokens)

def lexical_analyze(source_code, filepath):
    lexer = CLexer() if filepath.endswith(('.c', '.cpp')) else PythonLexer()
    
    tokens = []
    highlighted_code = highlight(source_code, lexer, HtmlFormatter())

    # Tokenize the source code and collect tokens along with their line numbers
    line_number = 1
    for line in source_code.splitlines():
        tokenized_line = lexer.get_tokens(line)
        for token_type, token_value in tokenized_line:
            tokens.append((str(token_type), token_value, line_number))
        line_number += 1
        
    return tokens, highlighted_code

if __name__ == '__main__':
    app.run(debug=True)
